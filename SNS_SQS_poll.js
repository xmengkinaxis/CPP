/*
try catch with retries with the exponential back-off. 

0. by default, it is short polling. might no message available
visibility timeout
dead-letter queues 
Amazon SQS message timers;  an initial invisibility period for a message added to a queue.

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
*/

// Import AWS SDK
const AWS = require('aws-sdk');
const assert = require('assert');
const LONGPOLL_SECONDS = 60; 
const MAX_RETRIES = 10; 

// Configure with the proper AWS region
AWS.config.update({ region: 'YOUR_REGION' }); 

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

    // long-poll SQS to receive packages
    const { Messages } = await sqs.receiveMessage({ QueueUrl: sqsURL, WaitTimeSeconds: LONGPOLL_SECONDS }).promise();
    
    if (Messages && Messages.length > 0) {
      const message = Messages[0].Body;
      assert.strictEqual(originalMessage, message);
      console.log('Received package from SQS:', message);

      await sqs.deleteMessage({ QueueUrl: sqsURL, ReceiptHandle: Messages[0].ReceiptHandle }).promise();
    } else {
      console.log('No message available in SQS.');
    }
  } catch (err) {
    console.error('Error receiving package from SQS:', err);

    // Implement retries with exponential backoff
    if (0 < maxRetries) {
      const delay = calculateDelay(Math.abs(MAX_RETRIES - maxRetries));
      console.log(`Retrying after ${delay} ms...`);
      await delayMs(delay);
      await receiver(sqsURL, maxRetry--); // Retry the receiver function
    }
  }
}

// Calculate the retry delay by using an exponential back-off algorithm 
function calculateDelay(retryCount) {
  const base = 1000; 
  const max = 100000; 
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

const URLs = ['SQS_QUEUE_URL_1', 'SQS_QUEUE_URL_2'];
let maxRetries = [5, 5];

for (let i = 0; i < URLs; ++i) {
  const url = URLs[i]; 
  let maxRetry = maxRetries[i];
  receiver(url, maxRetry);
}