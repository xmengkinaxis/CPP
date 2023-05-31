/*

0. SQS configuration
by default, it is short polling. might no message available
visibility timeout
dead-letter queues 
Amazon SQS message timers; an initial invisibility period for a message added to a queue.
FIFO: delete the first message; 

1. network issues
firewall restrictions, DNS resolution, network congestion(*)

2. incorrect queue URLs, 
double-click the queue URL, and ensure it is correct and points to the intended SQS queue; 

3. insufficient permissions, 
check IAM policies associated with the receiver's credential; 
must have the permission to receive and delete the messages from the queues; 

4. errors in the receiving code.
get the error message and exception

5. Enable logging 

6. Check CloudTrail

solution: 
try catch with retries with the exponential back-off. 

Reference: 
https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/sqs-visibility-timeout.html
The default visibility timeout for a message is 30 seconds. The minimum is 0 seconds. The maximum is 12 hours.
https://docs.aws.amazon.com/sdk-for-javascript/v3/developer-guide/javascript_sqs_code_examples.html 
https://docs.aws.amazon.com/sdk-for-javascript/v2/developer-guide/sqs-examples-send-receive-messages.html
https://docs.aws.amazon.com/sdk-for-javascript/v3/developer-guide/sqs-examples.html

*/

// Import AWS SDK
const AWS = require('aws-sdk');
const assert = require('assert');
const LONGPOLL_SECONDS = 60; 
const VISIBILITY_TIMEOUT_SECONDS = 10; 
const MIN_RETRIES = 3; 
const MAX_RETRIES = 10; 
const MY_REGION = 'us-east-1';

// Configure with the proper AWS region
AWS.config.update({ region: MY_REGION }); 

const originalMessage = 'Hello world';

// Sender
async function sender() {
  try {
    // Configure with the proper ARN of the SNS topic
    const topicArn = 'SNS_TOPIC_ARN';

    const sns = new AWS.SNS();
    await sns.publish({ TopicArn: topicArn, Message: originalMessage }).promise();
    console.log('message sent to SNS: ' + originalMessage);
  } catch (err) {
    console.error('Error of sending package:', err);
  }
}

// Receivers
async function receiver(sqsURL, maxRetry) {
  try {
    const sqs = new AWS.SQS();

    // long-poll SQS to receive a message
    const { Messages } = await sqs.receiveMessage({ 
      QueueUrl: sqsURL, 
      MaxNumberOfMessages: 1, 
      WaitTimeSeconds: LONGPOLL_SECONDS, 
      VisibilityTimeout: VISIBILITY_TIMEOUT_SECONDS 
    }).promise();
    
    if (Messages && Messages.length > 0) {
      const message = Messages[0].Body;
      assert.strictEqual(originalMessage, message);
      console.log('Received message:', message);
      
      if (maxRetry <= MIN_RETRIES) {
        delayMs(VISIBILITY_TIMEOUT_SECONDS * 2);
        console.log('delay as a long processing time:', message);
      } else {
        await sqs.deleteMessage({ QueueUrl: sqsURL, ReceiptHandle: Messages[0].ReceiptHandle }).promise();
        console.log('delete message:', message);
      }
    } else {
      console.log('No message available.');
    }
  } catch (err) {
    console.error('Error receiving message from SQS:', err);

    // Implement retries with exponential back-off
    if (0 < maxRetries) {
      const delay = calculateDelay(Math.abs(MAX_RETRIES - maxRetries));
      console.log(`Retrying after ${delay} ms...`);
      await delayMs(delay);
      await receiver(sqsURL, maxRetry - 1); // Retry the receiver function
    }
  }
}

// Calculate the retry delay by using an exponential back-off algorithm 
function calculateDelay(retryCount) {
  const base = 1000; 
  const max = 130000; 
  const factor = 2; 
  
  const delay = Math.min(base * Math.pow(factor, retryCount), max); 
  return delay; 
}

// Delay function
function delayMs(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}


// Run sender and receivers
sender();

const URLs = ['SQS_QUEUE_URL', 'SQS_QUEUE_URL'];
let maxRetries = [MIN_RETRIES, MAX_RETRIES];

for (let i = 0; i < URLs.length; ++i) {
  const url = URLs[i]; 
  let maxRetry = maxRetries[i];
  receiver(url, maxRetry);
}