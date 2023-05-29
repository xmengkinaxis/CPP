// Import AWS SDK
const AWS = require('aws-sdk');

// Configure AWS SDK
AWS.config.update({ region: 'YOUR_REGION' }); // Replace YOUR_REGION with your desired AWS region

// Create SNS and SQS instances
const sns = new AWS.SNS();
const sqs1 = new AWS.SQS();
const sqs2 = new AWS.SQS();

// Sender
async function sender() {
  try {
    const topicArn = 'YOUR_SNS_TOPIC_ARN'; // Replace YOUR_SNS_TOPIC_ARN with the ARN of your SNS topic

    // Send packages to SNS
    const message = 'Hello, package!'; // Replace with your package message
    await sns.publish({ TopicArn: topicArn, Message: message }).promise();
    console.log('Package sent to SNS.');
  } catch (err) {
    console.error('Error sending package:', err);
  }
}

// Receivers
async function receiver1() {
  try {
    const queueUrl1 = 'YOUR_SQS_QUEUE_URL_1'; // Replace YOUR_SQS_QUEUE_URL_1 with the URL of your first SQS queue

    // Poll SQS1 to receive packages
    const { Messages } = await sqs1.receiveMessage({ QueueUrl: queueUrl1 }).promise();
    if (Messages && Messages.length > 0) {
      const message = Messages[0].Body;
      console.log('Received package from SQS1:', message);

      // Delete the message from SQS1
      await sqs1.deleteMessage({ QueueUrl: queueUrl1, ReceiptHandle: Messages[0].ReceiptHandle }).promise();
    } else {
      console.log('No packages available in SQS1.');
    }
  } catch (err) {
    console.error('Error receiving package from SQS1:', err);

    // Implement retries with exponential backoff
    if (shouldRetry(err)) {
      const delay = calculateRetryDelay();
      console.log(`Retrying after ${delay} ms...`);
      await delayMs(delay);
      await receiver1(); // Retry the receiver function
    }
  }
}

async function receiver2() {
  try {
    const queueUrl2 = 'YOUR_SQS_QUEUE_URL_2'; // Replace YOUR_SQS_QUEUE_URL_2 with the URL of your second SQS queue

    // Poll SQS2 to receive packages
    const { Messages } = await sqs2.receiveMessage({ QueueUrl: queueUrl2 }).promise();
    if (Messages && Messages.length > 0) {
      const message = Messages[0].Body;
      console.log('Received package from SQS2:', message);

      // Delete the message from SQS2
      await sqs2.deleteMessage({ QueueUrl: queueUrl2, ReceiptHandle: Messages[0].ReceiptHandle }).promise();
    } else {
      console.log('No packages available in SQS2.');
    }
  } catch (err) {
    console.error('Error receiving package from SQS2:', err);

    // Implement retries with exponential backoff
    if (shouldRetry(err)) {
      const delay = calculateRetryDelay();
      console.log(`Retrying after ${delay} ms...`);
      await delayMs(delay);
      await receiver2(); // Retry the receiver function
    }
  }
}

// Retry condition
function shouldRetry(err) {
  // Add specific error conditions to check for retry
  // For example, you can check for network errors or specific AWS SDK errors
  // You can also set a maximum retry count and check if it has been reached
  return true;
}

// Calculate retry delay
function calculateRetryDelay() {
  // Implement exponential backoff algorithm to calculate the delay
  // You can increase the delay exponentially with each retry attempt
  return 1000; // Replace with your own logic
}

// Delay function
function delayMs(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}


// Run sender and receivers
sender();
receiver1();
receiver2();
