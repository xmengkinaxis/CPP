# System Design Interviews checklist

- [System Design Interviews checklist](#system-design-interviews-checklist)
- [0 Interview Preparation](#0-interview-preparation)
  - [0.1 Time Allocation](#01-time-allocation)
  - [0.2 Tips on the process](#02-tips-on-the-process)
  - [0.3 Communicate through process](#03-communicate-through-process)
  - [0.4 Goal and Purpose](#04-goal-and-purpose)
  - [0.5 Expectations](#05-expectations)
  - [0.6 Should do](#06-should-do)
- [1 Ask clarifying and high-level design Questions to scope the problem well](#1-ask-clarifying-and-high-level-design-questions-to-scope-the-problem-well)
  - [1.1 Functional Requirements (Product Features + User Requirements)](#11-functional-requirements-product-features--user-requirements)
    - [1.1.1 Product Features](#111-product-features)
    - [1.1.2 User requirements](#112-user-requirements)
  - [1.2 Non-Functional Requirements (Product Properties + User Expectations) (PACELC + reliable + Scalability + Extensibility)](#12-non-functional-requirements-product-properties--user-expectations-pacelc--reliable--scalability--extensibility)
    - [Availability](#availability)
    - [Consistency](#consistency)
    - [Efficiency (Latency and throughput)](#efficiency-latency-and-throughput)
    - [Scalability](#scalability)
    - [Reliability](#reliability)
    - [Concurrency](#concurrency)
    - [Serviceability or Manageability (simplicity):](#serviceability-or-manageability-simplicity)
    - [Durability](#durability)
    - [Security](#security)
  - [1.3 Achieve NFR (Non Functional Requirement)](#13-achieve-nfr-non-functional-requirement)
  - [1.4 Prioritize requirements](#14-prioritize-requirements)
  - [1.5 Design Considerations (no do, or assumption)](#15-design-considerations-no-do-or-assumption)
- [2 Capacity Estimation and Constraints: Traffic, Storage, Network/Bandwidth, Memory(cache) Estimation.](#2-capacity-estimation-and-constraints-traffic-storage-networkbandwidth-memorycache-estimation)
  - [2.1 Traffic in write/second, or read/second](#21-traffic-in-writesecond-or-readsecond)
  - [2.2 Storage in TB or GB/year](#22-storage-in-tb-or-gbyear)
  - [2.3 Bandwidth in KB/s or MB/s](#23-bandwidth-in-kbs-or-mbs)
  - [2.4 Memory (cache) in GB or TB /day](#24-memory-cache-in-gb-or-tb-day)
  - [2.5 Servers' capability](#25-servers-capability)
- [3 System API design](#3-system-api-design)
- [4 Database Design (Define Data Model and choose Database)](#4-database-design-define-data-model-and-choose-database)
  - [4.0 Data Model](#40-data-model)
  - [4.1 Database Schema or components/classes and their relationship/connection (static)](#41-database-schema-or-componentsclasses-and-their-relationshipconnection-static)
  - [4.2 Choose Database](#42-choose-database)
- [5 High-Level Design — This is pretty much a template, you can put in front of interviewers.](#5-high-level-design--this-is-pretty-much-a-template-you-can-put-in-front-of-interviewers)
- [6 Low-Level Design - Deep dive core components; detailed component design](#6-low-level-design---deep-dive-core-components-detailed-component-design)
  - [6.1 Scale the design](#61-scale-the-design)
  - [6.2 Partition and Replication (core of a distributed system, to scale out the system)](#62-partition-and-replication-core-of-a-distributed-system-to-scale-out-the-system)
    - [6.2.1 Replication](#621-replication)
    - [6.2.2 Partition](#622-partition)
      - [6.2.2.1 Horizontal Partitioning](#6221-horizontal-partitioning)
      - [6.2.2.2 Vertical Partitioning](#6222-vertical-partitioning)
- [7 Evaluation and Optimization](#7-evaluation-and-optimization)
  - [7.1 Evaluation](#71-evaluation)
  - [7.2 Security and Permissions](#72-security-and-permissions)
  - [7.3 Analytics - users behavior](#73-analytics---users-behavior)
  - [7.4 Performance monitor - system performance (telemetry)](#74-performance-monitor---system-performance-telemetry)
- [8 Trade-off](#8-trade-off)
  - [8.1 Common Trade-off](#81-common-trade-off)
  - [8.2 Partition](#82-partition)
  - [8.3 User connections (HTTP vs WebSocket)](#83-user-connections-http-vs-websocket)
  - [8.4 CDN Push vs Pull](#84-cdn-push-vs-pull)
  - [8.5 Newsfeed Push vs Pull](#85-newsfeed-push-vs-pull)
- [9 System Design Principles](#9-system-design-principles)
- [10 System Design Best Practices](#10-system-design-best-practices)
- [11 Scale](#11-scale)
  - [11.1 Load Balancers \& its algorithms - How to scale web servers (reverse proxy)](#111-load-balancers--its-algorithms---how-to-scale-web-servers-reverse-proxy)
    - [metrics:](#metrics)
    - [algorithms:](#algorithms)
  - [11.2 Caching - How to scale database?  Caching or vertically and horizontally](#112-caching---how-to-scale-database--caching-or-vertically-and-horizontally)
    - [Cache eviction policies:](#cache-eviction-policies)
    - [Cache expiration](#cache-expiration)
    - [Cache strategy (Invalidation):](#cache-strategy-invalidation)
  - [11.3 CDN -\> How to prepare our assets to deliver faster across the world?](#113-cdn---how-to-prepare-our-assets-to-deliver-faster-across-the-world)
  - [11.4 Cache, Scale, and Shard result](#114-cache-scale-and-shard-result)
    - [cache result==\> low latency, high throughput and high available (if db server is down for a while)](#cache-result-low-latency-high-throughput-and-high-available-if-db-server-is-down-for-a-while)
    - [Scalability result ==\> low-latency and fault-tolerant by replicate (deal with lower performance)](#scalability-result--low-latency-and-fault-tolerant-by-replicate-deal-with-lower-performance)
    - [Shard result==\> high performance by destructing the load and high available, and latency-free](#shard-result-high-performance-by-destructing-the-load-and-high-available-and-latency-free)
- [12 Components](#12-components)
  - [Load Balancers](#load-balancers)
  - [Key Value Stores](#key-value-stores)
  - [Blob Storage](#blob-storage)
  - [Database](#database)
  - [Rate Limiters](#rate-limiters)
  - [Monitoring Systems](#monitoring-systems)
  - [Distributed messaging queues](#distributed-messaging-queues)
  - [Distributed unique ID generators](#distributed-unique-id-generators)
  - [Distributed search](#distributed-search)
  - [Distributed logging services](#distributed-logging-services)
  - [Distributed task schedulers](#distributed-task-schedulers)
  - [Others](#others)
- [13 Common Design patterns](#13-common-design-patterns)
  - [13.1 Microservices](#131-microservices)
  - [13.2 Event Sourcing](#132-event-sourcing)
  - [13.3 CQRS (Command Query Responsibility Segregation)](#133-cqrs-command-query-responsibility-segregation)
  - [13.4 Circuit Breaker:](#134-circuit-breaker)
  - [13.5 Backpressure](#135-backpressure)
  - [13.6 Object Pool](#136-object-pool)
- [14 Q\&A](#14-qa)
  - [Single point of failure require--\> Redundancy and Replication](#single-point-of-failure-require---redundancy-and-replication)
  - [Checkpointing \<-- Fault Tolerance](#checkpointing----fault-tolerance)
  - [Fault Tolerance -\> Checkpointing, Load Balancer, Replication](#fault-tolerance---checkpointing-load-balancer-replication)
  - [Asynchronism](#asynchronism)
  - [Extensibility](#extensibility)
  - [Ranking](#ranking)
  - [Popular services:](#popular-services)
  - [Interview tool](#interview-tool)
  - [Questions:](#questions)
- [15 Future + ML](#15-future--ml)
- [16 Review, Evaluate, and Evovle](#16-review-evaluate-and-evovle)


<!-- TOC -->

# 0 Interview Preparation
## 0.1 Time Allocation
Clarify the problem, break down the complex problem into parts, discuss the overall design, and deep dive into some components; identify and analyze the tradeoffs, recover from the failures; <br>
1. understand the problem and establish design core: ~10 minutes (3 - 10 m)
2. Propose high-level design and get buy-in; -10 minutes (10 - 15 m)
3. Design deep dive; 20 minutes (10 - 25 m)
4. Wrap / Evaluation / feedback / discusson / question : 5 minutes (3 - 5 m)

## 0.2 Tips on the process
1. Discuss trade-offs with your interviewers
2. Manage your time efficiently
3. Start wide and end deep

## 0.3 Communicate through process
1. Start with the problem statement: clearly explain the problem and the requirements for the system; then explain your approach and how you plan to tackle the problem
2. Break down the problem: divide the problem into smaller parts and explain how you will solve each part individually
3. Use diagrams and sketches to help explain your design 
4. Explain the trade-offs you made and the constraints you considered; demonstrate you understanding of the problem and your ability to make informed decisions
5. Explain your reasoning: Clearly explain why you made certain design decisions and how they address the problem and requirements.  how you arrived at your solution.
6. Be prepared to answer questions and provide alternatives: 
7. Be open to feedback:  be prepared to revise your design based on feedback from the interviewer. This will demonstrate your ability to iterate and improve your design based on feedback.

Demonstrate your ability to anticipate and address potential issues in your design<br>
* Anticipate edge cases: high traffic, low memory, and high user concurrency
* Plan for failure: how to maintain availability and consistency
* Consider scalability
* Consider security: protect sensitive data and ensure security
* Be prepared to explain why you made certain design decisions and how they address edge cases and constraints.

## 0.4 Goal and Purpose 
* The key aspect of system design is to identify the problem area and trade off, and be able to justify a decision over another. <br>
* assesses a candidate's ability to combine knowledge, theory, experience, and judgment toward solving a real-world engineering problem with significant ambiguity. <br>
* Interviewrs are more interested in your thought process throughout the interview than in your final design. 
* The success heavily depends on your ability to communicate your thought process and hold a discussion (collaborate). <br>
* Demonstrate your thought process and domain-specific knowledge; Presentation matter.<br>
* It is critical to demonstrate your ability to recognize and evaluate trade-offs, as it reflects your understanding of various design aspects and their implications<br>

## 0.5 Expectations 
* Mid-level System Designers 
  * Be able to identify and address performance, scalability, and reliability issues
  * be well-versed in various architectural styles, design patterns, and their trade-off
* Senior System Designer
  * strong expertise on System Design
  * tackle some of the most challenging design issues
  * have the insight to address **long-term issues** that may affect a system over its lifetime
  * speak toward bottlenecks and long-term scalability of the system
  * feel confident enough to lead and mentor other designers in regard to system design principles, concepts, and best practices; 
  * Can review, evaluate, and evolve a system desgin
* Principle/Lead System Designer
  * extensive knowledge of System Design, **its history, and industry trends**; (past, current, and future)
  * be **recognized** for designing and implementing complex and large-scale systems; (have a good reputation)
  * have a deep and thorough understanding of trade-offs, performance optimizations, and long-term scalability

## 0.6 Should do 
* Get the skeleton in the place and then start optimizing (optimization is an evolutionary process) notch by notch; <br>
* Lead and drive an Open-ended conversation as doing a demo or presentation; or as guide juniors, discuss with peer, and present to seniors
* Everything is a trade-off; Make points with justification; Defend your design;
* Regularly monitor the time on track
* Evaluate the solution, and engage in feedback, discussion and question;
* Do NOT over-design or under-design;
* No single-point failure (to achieve highly reliable, no data lost)
* Identify potential bottlenecks and future problems (scale)
* Describe failover and impacts on users and Service Level Agreements (SLAs)
* Backup and disaster recovery
* Usage patterns, and security

* System design is similar to Object/Class Design. Why need such a class? Which method/function should it provide? Which information should it stores or manages?

# 1 Ask clarifying and high-level design Questions to scope the problem well
what an interviewer is expecting from us; the interviewer is evaluating your investigative abilities<br>
* to Gather requirements, and to scope the problem
* to outline use cases, to gather constraints, and to validate our assumptions
Whenever you interact with a platform, think of the who, why, what, and how. Looking into designing the incentives for all kinds of users for them to interact with the system. <br>

The functional requirements are the **features and functionalities** that the user will get, whereas the non-functional requirements are the **expectations in terms of performance** from the system. 

## 1.1 Functional Requirements (Product Features + User Requirements)
### 1.1.1 Product Features
* Goal: What is the goal? <br>
* Functions: What does the system do? <br>
* Input and output: What are the inputs and outputs of the system? <br>
* Criticality: What is the criticality of the system? <br>

### 1.1.2 User requirements
* User types: Who is going to use it? How many kinds of users are there? The categories of people. E.g.Creator, Viewer, and Advertiser.  <br>
* Purpose: Why? Their incentives to use the system. We develop the whats (incentives/procedures) and the whys (why someone would interact with that kind of content). <br>
* User cases: 
  * What are the use cases? <br>
  * How are they going to use it?  <br>
  * What kind of operations does the system support? <br>
  * Read-Heavery vs Write-Heavy

## 1.2 Non-Functional Requirements (Product Properties + User Expectations) (PACELC + reliable + Scalability + Extensibility)
CAP theory. CP or AP? PACELC (When Partition, Availability or Consistency, Else Latency or Consistency); High reliable and high scalable;  <br>
Reliability, Redundant, Stable, Security, Availability 100 up-time?, Simplicity vs Complexity, Maintainability, Consistency, or eventual consistency <br>

Need enough resources to handle the increasing load; the system must be simple so that it is easy to scale at any point in time; performance should always be increased with scalability. <br> 

### Availability 
* System must be highly available to keep the users engaged with the platform
* the percentage of the time that a system remains operational to perform its required function in a specific period under normal conditions; if a system is reliable, it is available. However, if it is available, it is not necessarily reliable.  <br>
* Every request received by a non-failing node in the system must result in a response. Refers to the system's ability to remain accessible even if one or more nodes in the system to go down. 
* Measured in a number of 9s, three 9s - 99.9%, four 9s - 99.99% <br>
* Availability = Uptime ÷ (Uptime + downtime);  <br>
* **Mean Time Between Failures (MTBF)**: total uptime / # of failures. This is the average time between failures.  <br>
* **Mean Time to Repair (MTTR)**: total downtime / # of failures. This is the average time taken to recover from a failure. <br>
* Availability can be **achieved** through CDN (Cache), redundancy (replica of servers and data) , load balancing (distribute the requests only to the active healthy nodes by local LB and to different locations by global LB), choosing high availability databases <br>

### Consistency
All nodes see the same data at the same time, no matter users read/write from/to any node. Equivalent to having a single up-to-date copy of the data. is the agreement between multiple nodes in a distributed system to achieve a certain value. <br>
* **Strong consistency**: the data in all nodes is the same at any time; offers up-to-date data, but at the cost of high latency. <br>
* **Weak consistency:** no guarantee that all nodes have the same data at any time.  <br>
* **Eventual consistency:** ensure data of each node of the database get consistent eventually; offers low latency at the risk of returning stale data. <br>
* high consistency on messages can be achieved with the help of a FIFO messaging queue with strict ordering

### Efficiency (Latency and throughput)
* Two standard measures of its efficiency are **the response time(or latency)** that denotes the delay to obtain the first item and **the throughput (or bandwidth)** with denotes the number of items delivered in a given time unit. (Metrics: Latency/Response Time, throughput/Bandwidth)
* **Response Time**: the time difference between request and response
* **Latency**: how long a system takes to transmit data from one point to another point in the system;
* **Throughput** is the amount of work done by the system in a given particular time. partition and split data, so they are served by different machines in the parallel read or write; cache at the different layers, including the client side, front-end servers, and databases
* **Bandwidth** is the maximum data that can be transferred on the different networks.
* Request Per Second;
* can be **achieved** by using multiple machines to parallel process; minimize the latency by geographically distributing servers and their caches, adding cache clusters on top of database clusters, and using CDNs for frequently sharing documents and media content
* video streaming should be smooth
* Performance can be achieved by Caching at each layer (web server, application server, cluster, data base, file system, storage units), CDN, Index, the appropriate programming language

### Scalability
* a distributed system can continuously evolve in order to support the growing amount of work; 
* increase resources and performance with increasing load and traffic over the existing system without affecting the complexity and performance; need enough resources to handle the increasing load, for it would be increased at any point in time; should be simple and easy to scale; performance should always be increased with scalability <br>
* A system can be called scalable if adding more resources in the system results in performance increases. Performance is directly proportional to resources added. <br>
* Horizontal (scaling out) vs Vertical Scaling (scaling up) <br>
* The system should be able to scale up and down, depending on the number of requests; Auto-scaling policies are crucial for maintaining the desired level of performance, availability, and cost efficiency <br>
* Scalability can be **achieved** through CDN (Cache which bring the content closer to user and remove the requirement of high bandwidth), reading replicas, partitioning data/files, horizontal sharding of database,  the isolation of different services (micro-services), load balancer, separate read/write operations on different server; optimize a general-purpose server for special tasks by carefull performance engineering of the full software stack <br> 
* Partition and split the big file/blobs into small-sized chunks to scale the requests, served by different partition servers; maybe range-based partition; need a partition mapping
* Storage, bandwidth, and the number of concurrent user request should NOT become bottleneck, or overwhelm any servers

### Reliability
* **Goal**: keep delivering its service even when one or several of its software or hardware components fail; handle faults, failures, and errors;  
  * A **fault** is a defect or flaw in the system's components. A fault is a defect or flaw in the system's hardware or software that can potentially cause the system to deviate from its expected behavior.
  * A **failure** is the visible manifestation of a system not performing as expected due to one or more faults.
  * An **error** is a human action or decision that can introduce faults or lead to failures in the system.
* **achieve** such resilience with a cost in order to eliminate every single point of failure (vulnerable), data lost, authentication(???)
  * client: 
    * use local storage, and resend after reconnect 
  * System: 
    * redundancy of the hardware, software components and data
    * load balancer: achieve with health check (heartbeat protocol, gossip protocol), and monitoring services with alerts.
    * services are decoupled and isolated; 

### Concurrency
To maximize system's performance: high bandwidth and high throughput.

### Serviceability or Manageability (simplicity): 
is the simplicity and speed with which a a system can be repaired or maintained. The ease of diagnosing and understanding problems when they occur, ease of making updates or modifications, and how simple the system is to operate

### Durability
The data, once uploaded, shouldn't be lost unless users explicitly delete that data. <br>
The replication and monitoring services ensure the durability of the data. <br>

### Security
Be secure via end-to-end encryption

## 1.3 Achieve NFR (Non Functional Requirement)
The table summarizing how to achieve various important attributes in system design:

| Attribute           | Strategies to Achieve                                                                                 |
|---------------------|------------------------------------------------------------------------------------------------------|
| High Availability   | - Redundancy and failover<br>- Load balancing<br>- Automated scaling<br>- Isolation<br>- Geographic distribution<br>- Disaster recovery planning<br>- Zero-downtime deployments<br>- Multi-region active-active architecture |
| Scalability        | - Horizontal scaling<br>- Microservices architecture<br>- Auto-scaling<br>- Distributed databases<br>- Caching<br>- Asynchronous processing<br>- Content delivery networks (CDNs) |
| Reliability         | - Redundancy<br>- Failover<br>- Monitoring and alerting<br>- Automated testing<br>- Backups and data replication<br>- Disaster recovery planning |
| Low Latency         | - Use of Content Delivery Networks (CDNs)<br>- Edge computing<br>- Distributed caching<br>- Efficient algorithms<br>- Optimized network architecture |
| High Throughput     | - Load balancing<br>- Horizontal scaling<br>- Distributed databases<br>- Use of asynchronous messaging<br>- Optimized data processing pipelines |
| Consistency         | - Strong consistency models<br>- Distributed transactions<br>- ACID compliance<br>- Event sourcing<br>- Eventual consistency for specific use cases |
| Concurrency         | - Proper locking mechanisms<br>- Isolation of critical sections<br>- Use of distributed locks<br>- Optimistic concurrency control |
| Security            | - Authentication and authorization mechanisms<br>- Encryption<br>- Firewalls<br>- Intrusion detection systems<br>- Regular security audits<br>- Least privilege principle |

Remember that achieving these attributes often involves trade-offs, and the strategies you choose will depend on your specific application requirements, budget, and the complexity you're willing to manage.

## 1.4 Prioritize requirements
Break it down, to the most important, minimal features for your system.

## 1.5 Design Considerations (no do, or assumption)
* Security: No user authentication or authorization; both are already completed <br>
* Result: get all or nothing, not a partial result;  <br>
* Fairness and ethical <br>
* Prevent abuse: put some restriction to stop system abuse, 
  * limit the size of text or image or video, 
  * add a rate limiter (prevent abuse behavior, provide a fair and reasonable use of the resource's capacity when sharing among many users, control the cost of operations and avoid excess costs) <br>
* assumption: surge in traffic <br>

# 2 Capacity Estimation and Constraints: Traffic, Storage, Network/Bandwidth, Memory(cache) Estimation.
The estimation will be helpful later when focusing on scaling, partitioning, load balancing, and caching <br>
What are the constraints? <br>

**Read-heavy vs Write-heavy**
* based on the read-heavy or write-heavy machine we can apply the 80–20 rule.  <br>
* If this is a **read-heavy**, estimate **read throughput**. <br>
* If a system is **write-heavy** then we need to estimate the **Storage** requirements per day, per year, and for 5–10 years. <br>


* **traffic** is the user request from users to servers
* **storage** is the user data or user-request data on disk 
* **bandwidth**  is traffic from servers to users
* **memory** is the cache capacity in order to improve the performance, esp. for read-heavy

## 2.1 Traffic in write/second, or read/second
**Users** <br>
* User types, e.g. riders vs drivers, guest vs owner <br>
* Total user <br>
* DAU (Daily active users) <br>
* Active connections per minutes <br>
* New users added per day <br>
* Meta data required for each user <br>

**Requests:** How many requests per second/day do we expect? <br>
* Type: (read, write, search); fast reads, fast writes, or both? <br>
* Count: write and Read count in million per day <br>
* Ratio: write : read ratio; generally 5 : 1 <br>
* Size: the average size of an reading or writing objects <br>

How much will it grow each year?

## 2.2 Storage in TB or GB/year
**Write:** Write count * write size; e.g. 400M * 300B = 120GB/day <br>
* Total files/write;  <br>
* average file/write sizes; Limit on user input for each paste or a certain time (text amount, image size, user URL size) (not abuse) <br>
* Metadata: user information, metadata about these writes <br>

**Total:** Total Storage Capacity including everythings
* **Others:** metadata, thumbnail, different resolutions, etc. <br>
* **Growth:** Estimate in 5 or 10 years; Growth rate? e.g. 120GB * 365 days * 5 years = 200TB <br>
* **Margin:** to keep some margin, If never more than 70% or 80% of capacity; Assuming a 70% capacity model (we don't want to go above 70% of the total capacity of our storage system); 200TB / 80% = 250TB <br>
* **Replication:** replication for fault tolerance; e.g. 250TB * 2 = 500TB; <br>
(500TB / 4T/server = 125 servers) (NOTE: too big for a single machine, so must be partitioned) (so is the cache) <br>

## 2.3 Bandwidth in KB/s or MB/s
Bandwidth will decide how to manage traffic and balance load between servers. ???  <br>
**Ingress (upload):** write count per second/minute * write average size <br>
**Egress (download, outgoing):** read count per second/minute * write average size <br>
**Ratio:** read or write intensive (need partition, or cache, or cache strategies) <br>

## 2.4 Memory (cache) in GB or TB /day
80-20 rule: 20% of hot pastes generate 80% of traffic, so only cache these 20% of pastes <br>
20% of daily traffic and based on client's usage patterns, can adjust how many cache servers we need <br>
20% * read count / per day * write average size  <br>

Benefit: Low latency (real time)

## 2.5 Servers' capability
Requests per second that a server can handle; used in estimating how many servers are required

# 3 System API design
**Goal:**<br>
The goal of the APIs is to make as much as clean & simple as possible to be simple to understand for everybody. A simple common way is making CRUDs. <br>
Establish the exact contract expected from the system and ensure if we haven't gotten any requirements wrong.  <br>
APIs can translate feature set into technical 

**Consideration:**<br>
Remember to use always a key for secure authentication; throttle users based on their allocated quota. <br>
Another consideration is to decide if our application will be Client Driver or Server Driver. <br>
Another consideration how do we want to split our requests ??? <br>
SOAP or REST API <br>

**Operations:** <br>
* CRUD (Create/paste/post, Read/get, Update/put, Delete) 
* Others (Search, list, store, stream, request, like or unlike, reply, follow or unfollow, retweet or re-post? or share? )
* these operations might work on different objects/levels/scopes
* Registration or authentication

**Parameters:** <br>
* user_id: uniquely specified th user performing the action;  throttle users based on their allocated quota <br>
* All kinds of information about the file/video/picture/like/dislike/comments/etc, like name/title, user/place ID, category/type, description, latitude, longitude, rating, hashtags, channel, language, privacy (private or public)<br>
* Search Query: category/type(videos, images, comments), keywords, user_location, radius, name_of_place  <br>
* maximum Results to Return:  <br>
* sort(number) Optional sort mode: 0 - latest first, 1 - best matched, 2 - most liked <br>
* page_token(string) specify a page in the result set that should be returned <br>
* Timestamp:  <br>

**Return:** <br>
(JSON) a list of results matching the search query <br>
e.g. This process returns a JSON object that contains a list of all the possible items in the specified category that also fall within the specified radius. <br>
Each entry has a place name, address, category, rating, and thumbnail.<br>

# 4 Database Design (Define Data Model and choose Database)

## 4.0 Data Model
**Benefit:** Defining the data model in the early part of the interview will 
* clarify how data will flow between different system components, 
* determine which database storage schema is required and which database type is preferred;
* guide for data partitioning and management.  <br>
  
**static and dynamic to identify**
* Identify various system **entities** (primary objects), 
* their **relationship** (static), 
* how they will **interact** with each other (dynamic, create, extract, transform, load), 
* how these objects **flow** between different system components.  <br>

**Consideration**
* Which database system should we use? NoSQL like Cassandra or MySQL?
* Separate the most frequently and less frequently accessed storage clusters from each other for optimal access time; can apply different configurations, cache strategies, shardings;  
* Separate the read and the write???

## 4.1 Database Schema or components/classes and their relationship/connection (static)
What to store? objects/entities, and their relations <br>
Table, Relationship <br>
Primary Key <br>
Foreign Key  <br>

Consideration for objects <br>
1. Does store billions of records (objects)? <br>
2. for each object, Is the object small (less than 1KB) or medium (a few MB, separated to object storage)? <br>
3. What is the relationship between records? <br>

Storage:  <br>
* Storage layer = **Metadata** storage + **Object** storage; such a division of data will allow us to scale them individually <br>
* Metadata storage: like users/accounts, pastes/blobs(pictures, videos, etc.), etc. can use Relational DB like MySQL, or distributed key-value DB like Dynamo or Cassandra <br>
* Object Storage: like a text paste, an image, etc; use object storage like Amazon S3, or HDFS.  <br>

Common objects (e.g.) <br>
* User: id (primary key, int), name (varchar 20), email (varchar 32), CreationDate (datetime, 4 byte?), LastLogin (datetime), Birthday (datetime) <br>
* Description (512 or 256), phone (12), path(256, path to the object storage) <br>
* Item/Object (picture, video, comment, etc): CreationData, ExpirationDate, type (int), Description (varchar 512), Category: (smallint), UserId(int, creator), contents(varchar 256), Path(varchar 256), likes_count, view_count <br>
* Location: latitude, longitude (int - 4 bytes, or 8 bytes) <br>
* Numbers: num of likes/dislikes (int), num of comments, num of shares, num of views <br>
* Rating (how many stars a place gets out of ten) <br>
* Photo: PhotoID(int, 8 bytes, 64 bits), UserID(int), Photo_Path(varchar 256), Photo Latitude & Longitude (int), User Latitude & Longitude (int), CreationDate(datetime), or Place_ID (8 bytes, foreign key) <br>
* Place: ID (8 bytes, 64 bits), Name(256 bytes), Description(1,000 bytes), Category (8 bytes ???), Latitude (8 bytes), Longitude (8 bytes), Phone(the foreign key, 8 bytes), Rating, address, business hours, menu
* Review: ID (8 bytes), Place_ID, User_ID, Description (512 bytes), Rating (1-5, 1 byte)

Tags:  <br>
category: (1 byte) <br>
default_language:  <br>

latest (CreationDate), popular (likes, comments, shares), relevant (used in ranking)   <br>

Index: <br>
* On which field(s) to build some index? <br>
* Pro: database performance =>  indexes to improve the performance of search queries, esp. when dataset is huge <br>
* Con: Dramatically speed up data retrieval, but slow down the write (insert, update, and delete) performance. <br>

the goal of creating an index on a particular table in a database is to make it faster to search through the table and find the row or rows that we want.  <br>
must carefully consider how users will access the data.  <br>
Indexing needs a primary key on the table with a unique value; Using one or more columns <br>
Ordered indexing (increasing or decreasing) or Hash-indexing <br>
In any index-based data, the partition is not allowed ??? <br>

## 4.2 Choose Database
choosing the proper database is a critical decision that can significantly impact the performance, scalability, and reliability of the system. <br>

Factors to consider (Data Model [structured/relational/columnar, semi-structure, unstructed], Size and Volume, ACID, Join and Aggregate)
* Data Model: Determine the data model that best fits the application's requirements; relational (SQL), document-based (NoSQL), key-value store, graph database, or time-series database.
* Data Size and Volume: Assess the expected data size and growth rate to choose a database that can handle the scale of data effectively
* Query Requirements: Understand the types of queries the system needs to support and whether they are read-heavy, write-heavy, or balanced.
* Performance: Consider the database's performance characteristics, such as read and write latency, throughput, and indexing capabilities.
* ACID Compliance: Determine whether the application requires strong consistency and transactional guarantees (ACID compliance) or can tolerate eventual consistency (NoSQL databases).
* Horizontal Scalability: Assess the need for horizontal scaling, i.e., distributing data across multiple nodes, and choose a database that supports sharding and partitioning.
* Data Integrity and Constraints: Evaluate the need for data integrity constraints (e.g., foreign keys, unique constraints) and choose a database that enforces these constraints.
* Data Redundancy and Normalization: Decide on the level of data redundancy and normalization based on read and write patterns, aiming for an appropriate balance between data duplication and normalization.
* Joins and Aggregations: Assess the frequency and complexity of joins and aggregations required in the queries and choose a database that can handle them efficiently.

* Replication and High Availability: Evaluate the need for data replication and high availability to ensure data durability and system resilience.
* Consistency Models: Understand the trade-offs between strong consistency and eventual consistency models and choose a database that aligns with the application's requirements.
* Backup and Disaster Recovery: Consider the database's backup and disaster recovery capabilities to ensure data safety.
* Cost and Licensing: Factor in the cost of database licenses, cloud service charges, and hardware requirements.
* Integration with Existing Tools and Systems: Assess whether the database integrates well with existing tools, frameworks, and systems used in the application.

# 5 High-Level Design — This is pretty much a template, you can put in front of interviewers.
**Goal** 
* The candidate should identify various system entities, how they will interact with each other, and how data would be flowing in the system
* static: components, their relationship and connections
* dynamic: workflow, how these components interact with each other, event/time sequences
  
**Steps**
* Outline a high level design with all important components and connections 
  * Draw a block diagram with 5-6 core components of the system, which are enough to solve the actual problem from end to end.
  * Map features to modules
  * Create micro-services based on features or APIs (e.g. which micro-service should handle request and reply with a response)
  * Sketch the main components and connections
  * Justify your ideas
* involved in the request flow from the client until the response is passed to the client. Describe the workflow based on the required operations

**Structure/Components (static):** 
Usually, a scalable system include (The Single Responsibility Principle advocates for small and autonomous services that work together to allow scale and configure them independently)
1. Client
2. Load balancer
3. WebServer (reverse proxy) / WebSocket / Front-end servers
4. Services (application layer, aka. platform layer) (Service Partition; list different services required, micro-services) 
5. Caching system
6. Database (master/slave cluster, partition and replication)

Others <br>
7. VPCs (publics, privates)<br>
8. Rate limiter<br>
9. Manager node: access privilege, console<br>
10. Monitoring service<br>

NOTE: 
Application layer will process all incoming and outgoing requests. 

# 6 Low-Level Design - Deep dive core components; detailed component design
Dig deeper into details of two or three major/core components; <br>
Pick or ask for; The interviewers' feedback should always guide us to what specific parts need focus, elaborate on, and further discussion.  <br>
(self choose some core components which are critical in performance)  <br>

Present different approaches, their pros and cons, and explain why we will prefer one approach over the other;  <br> 
Consider and Discuss potential solutions and trade-offs between different options while keeping system constrains in mind; <br>

How to handle XXX (a write or a read) request? If failed (such duplicated key), how to handle? <br>
pull vs push <br>

reduce latency by prefetch/pre-calculate, caching, parallelization/Asynchronous loading
Customer behavior can be predicted, and heavy customer requests can be pre-calculated and saved using customer proxy pre-cache.

## 6.1 Scale the design 
**Purpose** <br>
Identify, address, and mitigate bottlenecks and single point of failures using principles of scalable system design. <br>
1. Is there any single point of failure? a standby replica; Discuss as many bottlenecks as possible and different approaches to mitigate them
2. Identify and address bottlenecks, given the constraints.

**Approaches/Methods** <br>
1. Load balancer (avoid dynamic overheated or static overloaded) - What components need better load balancing? <br>
2. Caching 
   * client side - hold some meta data
   * server side - How much and at which layer should we introduce cache to speed thing up? can cache different objects for different services
3. Partition (horizontally scale, Database sharding); How to partition to distribute to multiple database (avoid uneven istribution [overloaded] and hotspot [overheated], user abuse behavior)
4. Replication - Define how the data will be replicated across servers, to achieve high availability; need to deal with consistency <br>
5. Index the database/tables to speed up list or search operations <br>

## 6.2 Partition and Replication (core of a distributed system, to scale out the system)
To mitigate the single point of failure and the performance bottleneck:  <br>
1. single point of failure: backup (snapshot periodically and add logs) or failover (fault tolerance)
2. bottleneck: improve load balancing and performance by creating duplicates/replication
3. consistency: The new problem introduced by replication

### 6.2.1 Replication 
**Replication:** the duplication of critical components or functions or data of a system, in the form of a backup or fail-safe (for fault tolerance) or to improve actual system performance (for load balancing); <br>
refers to keeping multiple copies of the data at various nodes(preferably geographically distributed) to achieve availability, scalability, and performance; <br>
the concepts of replication and partitioning go together; comes with the complexities, due to frequent changes, consistencies, concurrent writes, and fault tolerances<br>
* make multiple copies of data and store them on different servers. sharing information must ensure consistency between redundant resources by synchronously replicate data
* remove the single points of failures and provide backups in a crisis 
* It improves the availability, durability, reliability of data across the system 
* It can achieve load balance and fault tolerance. e.g. Primary and secondary, primary-replica relationship
* Keeping data geographically closer to the consumers of data to improve performance by reducing latency
* Tolerate failure in case some parts of the system fail.
* Scale the number of machines that can serve read queries.
* Replication factor: the number of copies of data, e.g. usually 3; for four copies: local copy to protect against server rank and drive failure, second copy in the other data center within the same region, and the third copy in a data center in different region to protect against regional disasters 

**Replication types** (need a trade-off between data consistency and availability) (dimension #1 timing)
* **Synchronous:** success after the primary node receive the acknowledgment from all secondary nodes; 
  * replicate within a storage cluster
  * pro: all secondary nodes are update to date; 
  * con: high latency if a secondary crashed without any acknowledge
* **Asynchronous:** report success after primary node updating itself; 
  * replicate across data centers and regions
  * pro: the primary can continue its work even if all secondary node are down; 
  * con: written data might be lost if the primary node is down

**Data replication models** (dimension #2 leadership)
* Single leader or primary-secondary (master-slave) replication; appropriate for read-heavy and read resilient, but not for write-heavy; primary is the bottleneck and the single point of failure; 
* Multi-leader (multi-master) replication;multiple servers can write data and are responsible for replicating data to each other. conflict when concurrent writes on the same data on the leaders; avoid conflicts, last-write-wins, or custom logic to handle conflicts
* Peer-to-peer or leaderless replication; all servers can both read and write data and are responsible for replicating data to other servers. quorums to solve the write-write inconsistency; Pro: more flexibility and improve performance for write-heavy workloads; Con: more complex to setup and manage;

### 6.2.2 Partition
**Partitioning (Horizontal or Vertical):** the technique to break a big Database into many smaller parts, and the process of distributing/splitting up a database/table across a set of servers. So that each database can only manage a subset of the data. <br> 
**Benefit** It is to improve the manageability, performance, scalability, availability (fault tolerance, non-availability of one type of data will not affect others), and load balancing of an application; access only a smaller fraction of data to run a query faster as there is less data to scan; reduce the overall response time <br>
Partitioning of relational data usually refers to decomposing your tables either row-wise (horizontally) or column-wise (vertically). <br>
for higher efficiency and lower latencies <br>

#### 6.2.2.1 Horizontal Partitioning
**Scaling horizontally (or scaling out)** means adding more instances of an application or service to share the load. conversely, scaling vertically (or scaling up) is about adding more resources, like CPU power or memory, to an instance. <br>

**Pro:** less read and write traffic, less replication, and more cache hit. Allow write in parallel with increase throughput. Index size is also reduced, which generally improve performance with faster queries. 

**Method:** 
 Horizontal partitioning (range based partitioning, Data Sharding) put different rows into different tables: 
   * Pros: statically in a predictable manner; 
   * Cons: unbalanced servers or hotspots, higher latencies, and unavailability)
  
e.g. Key-based (Hash) sharding; Range-based Sharding; Directory-Based Sharding (Dynamic Sharding)(by using a lookup table if the number is fixed) <br>
   * Hash-based Partitioning -> overloaded partition -> Consistent Hashing; 
     * Pros:evenly and randomly distribution, minimize hotspot, speed up the rebalancing process after adding or removing nodes, easier for clusters with heterogeneous machines; 
     * Cons: need to ask all and then aggregate the results
   * Range, list, hash partitioning; and combined partitioning (partition, and sub-partition); (partition based on the maximum capacity of the server); 
     * Pro: static and a predictable manner; 
     * Con: unbalanced
   * Directory Based Partitioning: a loosely coupled approach; the lookup/dictionary server that holds the mappings between each tuple key to its DB server. 
     * Pros: changing without an impact on the application

**Criteria:** (hash, range, RR, composite)
* Key or Hash-based partitioning; hash some key attributes of the storing entities to the partition number; consistent hashing to create a uniform distribution/allocation
* List partitioning; each partition is assigned a list of (key) values (sometime, similar to a range based partitioning, sharding)
* Round-robin partitioning
* Composite partitioning; any combination of the above partitioning schemes to devise a new one

**Rebalancing Reasons:** <br>
a. the distribution is not uniform (not evenly distributed)[overloaded] <br>
b. a lot of load on a partition (hotspot)[overheated] <br>

**Method: **<br>
a. Create more DB partitions; <br>
b. Rebalance existing partitions <br>

#### 6.2.2.2 Vertical Partitioning
Vertical partitioning: manually partition; divide data to store tables (divide table to store its columns) related to a specific feature/need in their own servers: 
* Pro: straightforward to implement and low impact on application; 
* Con: additional growth->further partition, joining two tables in two separate Db can cause performance and consistency issues;  <br>

Federation (functional partitioning) splits up databases by function, resulting in less read and write traffic to each database and therefore less replication lag; the database is smaller, easier to fit in memory and cache; write in parallel, increasing throughput. <br>
* Con: Update application logic to determine which database to read and write; join is more complex; more hardware and additional complexity.  <br>

**Problem:** on a partitioned database, there are some extra constraints on the operations that can be performed, esp. operations that across multiple tables or multiple rows in the same table, but on different servers <br>
* join and denormalization(data inconsistency): perform a cross-partition query on a partitioned database is not feasible; <br>
* Referential integrity (application have to enforce this); enforcing data integrity constraints such as foreign keys in a partitioned database can be extremely difficult; Database does not support; application that require referential integrity on partitioned database often have to enforce it in application code; <br> 
* Rebalancing: data distribution is not uniform (uneven, unbalanced, overloaded/underloaded); a lot of load on a partition (hotspot); <br> 

A large number of logical partitions to accommodate future data growth, vs a few physical database server. Such database server can have multiple database instances running on it. Use a configuration file to map the logical partitions to database server. So that can move partitions around easily.  <br>
For better performance and scalability, we can keep more shard than these just required.  <br>
Co-resident partitioning(on the same machine) is to reduce the size of individual indexes and reduce the amount of I/O (input/output) when updating records; <br>
Remote partitioning is to increase the bandwidth of access to the data by having more RAM, avoiding disk access, have more network interface and disk I/O channels available.  <br>

How to map a particular piece of data to its node? How to move and minimize data movement when adding or removing nodes? => consistent Hash. 

Other consideration: evenly distribute the load, no hotspot

# 7 Evaluation and Optimization
Compare your design to the requirements, and acknowledge any trade-offs made and improving aspects of design 

## 7.1 Evaluation 
* Goal: Evaluate how the system fulfill the non-functional requirements, 
* What to evaluate: 
  * Availability
  * Scalability
  * Reliability
  * Consistency
  * Fraud detection
  * anything in non-functional requirements
* How to evaluate: 
  * Evaluate each component from front to end, including load balancer, CDN, web servers, application servers, database, blob storage, Cache
  * Evaluate each non-functional requirement

## 7.2 Security and Permissions
1. Privacy  
2. Security (certification and authentication)
3. Throttle (API rate limiting) (against abusive behaviors, misbehavior, spikiness in traffic) 
	* Rate Limiting is limiting the amount of operation that can be done in a limited amount of time. e.g. security ramification, performance ramification. 
	* It is a defensive measure for services, protect the system from flooding with the traffic, for denial of service (DOS)
	* types: Hard throttling (hard limit, discard when exceed), Soft throttling (can exceed by a certain percentage), Elastic or dynamic throttling (can cross the predefined limit if the system has excess resources available)
4. International Law (e.g. restriction on video contents)

## 7.3 Analytics - users behavior 
Purpose: Get some insight on how users use the system 
a. Collect information on user behaviors from where ???
b. Analyze
c. Predict or forecast
d. Adjust based on the user's usage/login pattern (when and frequency)

logging request and response ???

## 7.4 Performance monitor - system performance (telemetry)
Performance: low latency (for single request) and high throughput (most/overall requests) for the clients; <br>
Purpose: Get an instant insight on how our system is doing (get an understanding of the performance of the service); address latency and throughput; 
Is the visibility to system health, system performance, and general statics; gather meaningful matrix (metrics/counters) and have tools to monitor these matrix;
a proper monitoring and logging system. 

* Collect data constantly - which component do so?
How many are the actual daily active users? user locations, date and time of their access
When is the daily peak?
How is the average latency?

* Alert when critical component fail or their performance degrade
* Determine if we need more load balancing (scaling), or caching, or replication, or further partitioning. 

# 8 Trade-off 
* Goal
Every solutions comes with a trade-off. The goal is to choose the solution with the most workable trade-off, which does not severely impact the most importatnt requirements of the system. <br>

* Step
  1. Explore competing solutions 
  2. Speak to all their major tradeoffs
  3. Make intelligent decisions about how to balance each of those tradeoffs

* Considering 
the user's needs, business goal, resource limitations, conflicting requirements, design constraints, and the prioritized user cases

## 8.1 Common Trade-off
  * Consistency vs Availability (strong consistency can impact availability; prioritizing availability might result in eventual consistency); choose based on business requirements in case of network partition; e.g. consistency rather than availability for WhatsApp; 
  * Performance vs Scalability (complex algorithm and data structure vs simpler components)
  * Data Integrity vs Performance
  * Short-Term vs Long-Term Goals (Immediate deliverables, potential technical debt vs Sustainable solutions, potential delays in short-term goals)
  * Reliability vs Cost
  * Security vs Usability
  * Security vs Latency (secure with encryption, vs real-time experience); e.g. Security rather than latency for WhatsApp
  * Monolithic vs Microservices Architecture (Monolithic is simpler to develop and deploy, but lack the scalability and fault isolation of microservices; microservices offer better scalability but introduce complexity in terms of communication and management)
  * Real-time processing vs Batch Processing
  * Data Normalization vs Denormalization (Normalized database reduced data redundancy, but can be slower for certain query patterns; Denormalization can improve query performance, but might lead to data integrity issues)
  * Caching vs Freshness
  * Centralized Control vs Decentralized Autonomy (simplify management, but be a single point of failure; vs more autonomy, but lead to inconsistencies or conflicts)

## 8.2 Partition
* Partition 
	* based on user ID or Tweet/Status ID or Hybrid or based on creation time or combination of tweet id and creation time
		* User ID; can do transaction; con: hotspot/high latency, unbalanced/uneven/non-uniform distribution, unavailability of all of the user's data;  
		* Tweet ID; dedicate two separate database instances (with a load balancer), one even-numbered IDs and the other odd-numbered, to generate auto-incrementing IDs; con: no able to do batch operation; 
		* Tweet Creation Time
		* Combination of Tweet ID and its Creation Time (Encode the creation time into Tweet Id, e.g. Epoch Second || auto incrementing sequence)				
	* range-based or hash based 
* Database: RDBM SQL vs NoSQL

## 8.3 User connections (HTTP vs WebSocket)
* use HTTP long polling or webSocket<br>
  * HTTP(S) does not keep the connection open for servers to send frequent data to a client. It uses polling. 
  * WebSocket maintains a persistent bidirectional connection between the client and a server, and can send asynchronous updates from a server to a client. 
* Poll (normal/Periodical poll): client <- bandwidth -> server
  * have a delay on client, 
  * waste bandwidth, 
  * keep the server busy;
* Push 
  * can give a lot of improvement in latencies, throughput, and performances<br>

## 8.4 CDN Push vs Pull
* Pull CDN: first client request is slower. Time-To-Live; suitable for serving dynamic content; favored for frequently changing content and a high traffic load; low storage consumption
* Push CDN: full response to upload content to the servers and rewriting URLs to point to the servers; appropriate for static content delivery; need more replicas than pull CDN
	* Traffic: heavy traffic works well with Pull CDN.  less traffic works well with Push CDN; 
	* Configuration: Pull CDN is easier to configure than Push CDN: 
	* Content Update: Sites with higher no of frequent updates work well with Pull CDN

## 8.5 Newsfeed Push vs Pull 
* Push vs Pull (or hybrid).e.g in notification, in CDN; (celebrity user) (online only); (not more than 10 from a single user to avoid spamming) in newsfeed 
* **Push**: The process of pushing a post to all the followers is called **fanout**. The push fanout is called **fanout-on-write**
* **Pull**: while the pull fanout is called **fanout-on-load**. 
* A combination of 'push to notify and 'pull for serving' <br>

* Pull: regularly or manually on demand
  * Pro: mobile does not waste data plan, 
  * con: not real-time/in-time, feeds becomes stale, most requests will result in an empty response and waste resources (bandwidth, server CPUs)<br>
* Push: need main a long poll request; 
  * Pro: immediately get the updates
  * Con: celebrity users who has millions of followers, the server pushes update too frequently<br>
* Hybrid: 
  * the users who have a high number of followers to a pull-based model 
  * only push data to those who have a few hundred/thousand follows; 
  * or the server pushes update to all the users not more than a certain frequency and letting users with a lot of updates to pull data regularly<br>

# 9 System Design Principles
System design principles are fundamental guidelines and concepts that help software engineers and architects create effective, efficient, and maintainable software systems. These principles provide **a framework for making decisions about the architecture, structure, and behavior of a system**. They aim to ensure that the resulting system meets both its functional and non-functional requirements while **being adaptable to changes and scalable**. Here are some key system design principles:

1. **Modularity and Separation of Concerns**:
   - Divide the system into smaller, manageable modules with distinct responsibilities.
   - Each module should focus on a single aspect or concern of the system.

2. **Abstraction**:
   - Hide complex implementation details behind well-defined interfaces.
   - Abstractions make components easier to use, understand, and modify.

3. **Encapsulation**:
   - Restrict access to internal details of a component and expose only necessary functionalities.
   - Encapsulation promotes information hiding and helps manage complexity.

4. **Single Responsibility Principle (SRP)**:
   - Each module or class should have a single reason to change.
   - Promotes maintainability by reducing the impact of changes.

5. **Open/Closed Principle**:
   - Software entities (classes, modules) should be open for extension but closed for modification.
   - Encourages designing systems that can be easily extended without altering existing code.

6. **Dependency Inversion Principle**:
   - Depend on abstractions rather than concrete implementations.
   - Helps reduce coupling between components and promotes flexibility.

7. **Liskov Substitution Principle**:
   - Objects of a derived class should be substitutable for objects of the base class without affecting program correctness.
   - Ensures that derived classes adhere to the behavior expected by clients.

8. **Interface Segregation Principle**:
   - Clients should not be forced to depend on interfaces they do not use.
   - Encourages designing fine-grained interfaces tailored to specific client needs.

9. **Composition over Inheritance**:
   - Favor composition (building objects from smaller parts) over inheritance (creating new classes from existing ones).
   - Composition is more flexible and avoids some limitations of class hierarchies.

10. **Keep It Simple and Stupid (KISS)**:
    - Strive for simplicity in design and avoid unnecessary complexities.
    - Simple designs are easier to understand, maintain, and troubleshoot.

11. **Don't Repeat Yourself (DRY)**:
    - Avoid duplicating code or logic. Instead, use abstractions to eliminate redundancy.
    - DRY promotes maintainability and reduces the risk of inconsistencies.

12. **Separation of Concerns (SoC)**:
    - Divide a system into distinct sections that address different aspects (e.g., user interface, data storage, business logic).
    - Separation improves modularity and allows independent development of components.

13. **Scalability**:
    - Design systems that can handle increased loads and growth without sacrificing performance or stability.
    - Consider techniques like horizontal scaling, load balancing, and caching.

14. **Performance Optimization**:
    - Optimize critical parts of the system while considering trade-offs.
    - Profile and benchmark the system to identify bottlenecks.

15. **YAGNI (You Aren't Gonna Need It)**:
    - Avoid adding features or functionality that aren't currently needed.
    - YAGNI prevents unnecessary complexity and allows the system to evolve based on actual requirements.

These principles guide architects and developers in making informed decisions throughout the system design process. Applying these principles leads to systems that are more maintainable, adaptable, and aligned with the goals of the project.


# 10 System Design Best Practices
System design best practices are guidelines and strategies that help software architects and engineers create high-quality, efficient, scalable, and maintainable software systems. These practices are based on industry experience and lessons learned, aiming to ensure that the resulting systems meet both functional and non-functional requirements. Here are some key system design best practices:

1. **Understand Requirements**:
   - Thoroughly understand the requirements of the system before beginning the design process.
   - Engage with stakeholders to gather and clarify requirements.

2. **Prioritize Non-Functional Requirements**:
   - Consider factors like performance, scalability, security, and availability from the outset.
   - Address non-functional requirements early in the design to avoid costly changes later.

3. **Divide and Conquer**:
   - Divide the system into smaller, manageable components or services.
   - Each component should have a well-defined responsibility.

4. **Use Design Patterns**:
   - Leverage well-known design patterns to solve common architectural challenges.
   - Patterns improve consistency and help communicate design decisions.

5. **Choose the Right Architecture**:
   - Select an architecture (monolithic, microservices, etc.) that aligns with the system's requirements and goals.
   - Consider trade-offs like maintainability, scalability, and complexity.

6. **Data Modeling**:
   - Design the data model based on the requirements and relationships between data entities.
   - Normalize or denormalize the data schema based on access patterns and performance considerations.

7. **Scalability and Performance**:
   - Plan for scalability by designing components that can be horizontally scaled.
   - Use caching, load balancing, and distributed architectures to improve performance.

8. **Security Considerations**:
   - Implement security measures, including authentication, authorization, and data encryption.
   - Address potential vulnerabilities early in the design process.

9. **Decoupling and Loose Coupling**:
   - Minimize dependencies between components to allow for easier changes and replacements.
   - Use well-defined interfaces to achieve loose coupling.

10. **Testing and Quality Assurance**:
    - Design for testability by creating components that can be easily tested in isolation.
    - Implement automated testing for both unit and integration tests.

11. **Documentation**:
    - Document the architecture, design decisions, and rationale behind choices.
    - Provide clear API documentation for components and interfaces.

12. **Version Control and Collaboration**:
    - Use version control systems to track changes and collaborate effectively.
    - Encourage code reviews to ensure code quality and share knowledge.

13. **Code Maintainability**:
    - Follow coding standards and guidelines for consistent and readable code.
    - Refactor code regularly to improve maintainability.

14. **Performance Profiling and Optimization**:
    - Profile the system to identify performance bottlenecks and optimize critical parts.
    - Focus optimization efforts on areas that have the most impact.

15. **Continuous Integration and Deployment (CI/CD)**:
    - Implement CI/CD pipelines for automated testing and deployment.
    - Automate deployment processes to ensure consistency and reduce human errors.

16. **Monitoring and Analytics**:
    - Implement monitoring and logging to track system behavior and detect issues.
    - Use analytics to gather insights into user behavior and system performance.

17. **Evolution and Flexibility**:
    - Design systems that can evolve over time to accommodate changing requirements.
    - Build in flexibility to add new features and components as needed.

By following these best practices, you can create software systems that are more resilient, maintainable, and aligned with the needs of both users and stakeholders.

# 11 Scale

## 11.1 Load Balancers & its algorithms - How to scale web servers (reverse proxy)
LB helps to 
* Scaling
  1. spread the traffic across a cluster of servers; facilitate scaling either up or down
* Availability
  1. prevent a single point of failures,  
  2. improve overall responsiveness and availability of application, websites or databases, 
* Performance
  1. achieve maximum throughput; 
  2. minimize response time (latency)
  3. improve overall responsiveness and availability of application, websites or databases, 
* Others
  1. optimize resource usage (avoid overload and under-load of any machine);  
  2. keeps tracks of the status of all the resources; 
   
To utilize full scalability and redundancy, try to balance the load at each layer of the system;<br>
faster, higher throughput, easier for administrators, predictive analytics to determine traffic bottlenecks, give actionable insights to automation and help drive business decisions.
LB helps scale horizontally across an ever-increasing number of servers.<br>

### metrics: 
* active Connections (session affinity or sticky session) <br> 
* Latency <br>
* Bandwidth(throughput) <br>
* random (Round Robin or Hash) <br>

algorithm categories: 
* static vs dynamic
	* static (simple, based on the server's configuration) [RR, weighted, IP hash] <br>
	* dynamic (complex, but better; consider the current state and healthy of the servers) [LCM, LRM, LBM]<br>
* stateful vs stateless
	* stateful: complex; maintain the state of the sessions established between clients and hosting servers; share the state information among load balancers <br>
	* stateless: faster and lightweight; use consistent hashing <br>
* implementation 
	* hardware (expensive): can handle concurrent users; poor availability; high cost and less flexible <br> 
	* software.e.g HAProxy (layer 4 or 7), NGINX; flexibility, programmability, and cost-effectiveness; predictive analysis <br>
* layers:
	* Layer 4 - transport layer (TCP/UDP); faster; source and destination IP, port; maintain connection/session<br>
	* Layer 7 - application layer; make application-aware forwarding decisions based on HTTP headers, URLs, message, cookies and other application-specific data like user ID; can take responsibilities like limiting user, HTTP routing, and header rewriting<br>
* multiple tiers
	* tier - 0 or 1: based on IP, use RR and Weighted RR
	* tier - 2: layer 4 LB; maintain connections/sessions; consistent hashing; 
	* tier - 3: layer 7 LB; enable scalability and provide high availability; offload TLS/SSL

### algorithms: 
* The choice of algorithm depends on the specific needs and characteristics of the system and the workload being handled<br>
* Least connection Method, LCM (servers with fewest active connections)<br>
* Least Response Time Method, LRM (servers with lowest average response time)<br>
* Least Bandwidth Method, LBM (lowest MB/s traffic)<br>
* Round Robin: does not take server load into consideration, RR; can overloaded<br>
* Weighted Round Robin Method, WRR<br>
* IP Hash (IP Address affinity)<br>
* Random : Simple to implement and no overhead<br>
* By HTTP Header or URL <br>
* By request parameters of the query string<br>


Con: <br>
a. performance bottleneck, if it does not have enough resources or it is not configured properly<br>
b. increase the complexity (be stateless, session can be stored in a centralized data store)<br>
c, single point of failure<br>

## 11.2 Caching - How to scale database?  Caching or vertically and horizontally
Cache the DB results adding an extra caching layer between the servers and the database <br>
A cache is a key-value store that reside between applications and data storage; <br>
Redis is persistent while memcache scales well.

**Benefit**
* Cache will enable you to make vastly better use of the resources you already have as well as making otherwise unattainable product requirements feasible. <br>
* Can exist at all levels in architecture, but are often found at the level nearest to the front end, where they are implemented to return data quickly without taxing downstream levels. <br>
What should be cached? long-running queries on databases; high-latency network requests (for external APIs), computation-intensive processing; <br>

**Disadvantages**: 
* main consistency between caches and the source of truth (database) through cache invalidation which is difficult; need to make application changes<br>
* Caching works well with static data by saving time and increasing speed, but not well with mutable or dynamic, for need to make sure that the cached data is in sync<br>

**CDN (Content Delivery Network)** are a kind of cache that comes into play for sites serving large amounts of static media. Can replicate content in multiple places, based on user's geographic location and the original of the webpage; security improvement, increase in content availability and redundancy, better load times, low bandwidth cost.  <br>
* type: Push and Pull, referring the data streaming upload and download???<br>

### Cache eviction policies:
Eviction policy determines how the cache handles the replacement of old data with new data when the cache is full
Policies: Order (first vs last), Recently (time: least vs most), Frequency (least), Random;<br>
* Order
	* First In First Out (FIFO), time-serious ???<br>
	* Last In First Out (LIFO)<br>
* Recent
	* Least Recently Used (LRU), suitable for long-tailed<br>
	* Most Recently Used (MRU)<br>
* Frequency
	* Least Frequently Used (LFU)<br>
* Random Replacement (RR)<br>

### Cache expiration
Determine how long data is kept in the cache before it is considered stale and is removed.<br>
A shorter expiration time can improve the freshness of the data, but increase the number of accesses to the underlying data source

### Cache strategy (Invalidation): 
Cache Invalidation: keep the cache coherent with the source of data (e.g. database);  <br>
strategy: cache and permanent story like disk or database, write only one or both; depend on the data and data access patterns (how data is written and read)  <br>
metrics: read-intensive vs write-intensive (write-write, write-reread); latency and throughput; consistency and data loss;<br>   

* Cache aside: general purpose, work best for read-heavy workloads; usually write-around, use write-through or Time To Live(TTL) to invalidate cache in order to avoid the stale data; The application is responsible for reading and writing from the storage. The cache does not interact with storage directly. Application load the entry from database, add it to cache and then return it to user. Lazy loading. Only requested data is cached.<br>   
* Read-through  <br>
* Write-through (both): data is written into both cache and database simultaneously. The application uses the cache as the main data store, reading and writing data to it, while the cache is responsible for reading and writing to the database synchronously. pros: fast retrieval, consistency between cache and storage, minimizes the risk of data loss; cons: higher latency for write operation; data written might never be read.   <br>
* Write-around (storage only): data is written into the permanent storage only (bypassing the cache). pros: cache is not flooded with written operation which is not subsequently be re-read. con: higher latency for the recently written data, for cache-miss, so higher latency; <br>   
* Write-back (write-behind)(cache only): the data is written to cache alone; asynchronously write entry to the data store. pros: low-latency and high-throughput for write-intensive applications. con: risk of data loss; more complex to implement, for its asynchronously writing.  <br> 

## 11.3 CDN -> How to prepare our assets to deliver faster across the world?
Real-time and low-latency require
* Replication of servers and server's location close to users (CDN) 
* PULL vs PUSH: real-time (VOIP, video, notification system and real-time feeds) : push (message queue), not pull(expensive in bandwidth and unnecessary load on Servers and DB, not scalable)

## 11.4 Cache, Scale, and Shard result
### cache result==> low latency, high throughput and high available (if db server is down for a while)
caching will enable you to make vastly better use of the resources you already have; 
application caching, database caching (need tweaking the configuration), in-memory caches

In-memory caches: 
precalculated results, pre-generating expensive indexes, storing copies of frequently accessed data in a faster backend

### Scalability result ==> low-latency and fault-tolerant by replicate (deal with lower performance)
Scalability methods—With the architecture, there are many techniques and methods which can be used in order to customize and improve the design of a system.<br> 
Some of the most widely used are: redundancy, partitioning, caching, indexing, load balancing, and queues.<br>

### Shard result==> high performance by destructing the load and high available, and latency-free

# 12 Components
every building block in system design has functional and nonfunctional requirements that must be met.

## Load Balancers
Evenly distributing the computational load allows for faster response times and the capacity for more web traffic.<br>
* Scaling: Load balancers facilitate scaling, either up or down, by disguising changes made to the number of servers.
* Availability: By dividing requests, load balancers maintain availability of the system even in the event of a server outage.
* Performance: Directing requests to servers with low traffic decreases response time for the end user.

## Key Value Stores
Similar to Hash table or dictionaries. Store information as a pair in the Key and Value format, for easy retrieval. Distributed hash tables (DHT). <br>
e.g. AWS DynamoDB, AWS ElastiCache (a managed in-memory data store serivce which supports caching, like Redis or Memcached) (Redis, in particular, supports advanced data structures and features that make it effective for caching.<br>
When it comes to caching user information effectively, Amazon ElastiCache with Redis is often a preferred choice due to its advanced caching capabilities, data structures, and support for use cases like user sessions and frequently accessed data.  However, the choice of service will depend on factors such as the complexity of the data, required data structures, access patterns, and performance requirements. <br>

## Blob Storage
Blob: Binary Large Object; a storage solution for unstructured data, such as photos, audios, multimedia, executable code; uses flat data organization pattern without hierarchy<br> 
The main rule: write once, read many or WORM. Ensure the important dat is protected since once the data is written, it can be read, but not changed. <br>
e.g. AWS S3

## Database
A database is an organized collection of data that can be easily accessed and modified; make the process of storing, retrieving, modifying, and deleting data simpler. SQL vs NoSQL <br>

## Rate Limiters
It sets a limit for the numbers of requests a service will fulfill. It will throttle requests that cross this threshold.<br>
It is an important line of defense for servies and system; prevent services being flooded with requests; mitigate resource consumption.<br>
e.g. AWS API Gateway(built-in rate limiting on request/API/method per second/minute/others), AWS WAF(Web Application Firewall, restrict requests from the specific IP address or IP address ranges); <br>
AWS Lambda, AWS CloudFront (CDN, request rate limiting to prevent abuse and ensure a smooth experience for users), AWS ELB(Elastic Load Balancing, configure specific rules as rate limiting)

## Monitoring Systems
It is a software that allow system administrators to monitor infrastructure. It creates one centralized location for observing the overall performance of a potentially large system of computers in real time. <br>
It can monitor: CPU, memory, bandwidth, routers, switches, applications, etc. e.g. AWS CloudWatch; AWS CloudTrail, X-Ray, Inspector, Trusted Advisor, and Config

## Distributed messaging queues
A producer creates messages and consumers receive and process them. <br>
* Improve performance through asynchronous communication since producers and consumers act independently of each other
* Decouple or reduce dependency in the system
* Improve reliability and allow simpler and less cluttered system design 
* Asynchronous messaging facilitates scalability, for more consumers can be added to compensate for the increased load
  
Usage: 
 * Sending emails
 * Data post-processing: It can reduce end-user latency, by enabling offline time-consuming and resource-intensive process, such as processing image, video, multimedia to different formrat or platforms<br>
 * Recommender systems: use cookies to personalize a user’s content; retrieves the user data and processes it. A messaging queue can be incorporated to make this process more efficient as background data processing can be time consuming.

## Distributed unique ID generators
It is important to tag entities in a system with a unique identifier. Millions of events may occur every second in a large distributed system, so we need a method of distinguishing them. A unique ID generator performs this task and enables the logging and tracking of event flows for debugging or maintenance purposes.<br>
In most cases this is a universal unique ID (UUID). These are 128 bit numbers<br>
Range handlers feature multiple servers that each cover a range of ID values.<br>

## Distributed search
Search systems are composed of three main entities: <br>
* Crawler: finds/fetches content and creates documents
* Indexer: builds a searchable index
* Searcher: runs the search query against the index
Distributed search systems are reliable and ideal for horizontal scalability<br>
E.g. Elasticsearch <br>

## Distributed logging services
Logging is the process of recording data, in particular the events that occur in a software system. A log file may document service actions, transactions, microservices, or any other data that may be helpful when debugging. <br>
Logging in a microservice architecture is convenient because the logs can be traced along a flow of events from end-to-end. Since microservices can create interdependencies in a system, and a failure of one service can cascade to others, logging helps to determine the root cause of the failure.<br>
e.g. AWS CloudWatch logs: Centralized Log Storage, Scalable and Distributed, Real-Time Monitoring, Search and Query, Retention and Archiving, Integration with Other AWS Services, Access Control and Security, CloudWatch Metrics Integration, Automated Actions <br>

## Distributed task schedulers
A **task** is a unit of work that requires computational resources, like CPU time, memory, storage, and network bandwidth, for some specified amount of time.<br>
It is important for tasks like image uploading or social media posting to be asynchronous as to not hold the user waiting for background tasks to end.<br>
Task schedulers mediate the supply-demand balance between tasks and resources to control the workflow of the system. By allocating resources task schedulers can ensure that task-level and system-level goals are met in an efficient manner. It is widely used in systems like Cloud Computing Services, Large Distributed Systems, and Single-OS-base nodes<br>

## Others
* Domain Name System (DNS)
* Content Delivery Network (CDN)
* Distributed Caching
* Publish-Subscribe System
* Sharded Counters

# 13 Common Design patterns

## 13.1 Microservices
An application is broken down into a collection of small, independent services that communicate with each other over a network. Each service is responsible for a specific functionality and is developed, deployed, and scaled independently. <br>
Pro: increased scalability, improved fault tolerance, and faster deployment cycles. <br>
Con: additional complexity, such as service discovery and inter-service communication; <br>

## 13.2 Event Sourcing 
the state of an application is represented as a stream of events, rather than a snapshot of its current state. This pattern is often used in systems that need to handle a large number of concurrent updates, such as financial systems and gaming platforms. <br>
Pro: easy replay of events, which can be useful for debugging and auditing<br>
Con: requires additional storage and computational resources to maintain the event stream<br>

## 13.3 CQRS (Command Query Responsibility Segregation)
separates the read and write operations of a system into separate models, allowing for optimized performance and scalability. This pattern can be useful in systems that handle a high volume of read and write operations, such as e-commerce websites<br>
Pro: allows for different data stores and caching strategies to be used for read and write operations, improving the performance of both <br>
Con: requires more complex design and more effort to maintain two separate models of the data. <br>

## 13.4 Circuit Breaker: 
can be used to prevent cascading failures in a distributed system. It works by monitoring the health of a service and, when it detects an issue, it “trips” and prevents further requests from being sent to that service. <br> 
Pro: This helps to prevent a single point of failure from bringing down the entire system. <br>

## 13.5 Backpressure
used to control the rate at which data is processed in a system, preventing it from being overwhelmed. This can be done by buffering incoming data and only processing it at a specific rate, or by rejecting incoming data if the system is unable to handle it.

## 13.6 Object Pool
is used to improve the performance of a system by reusing objects, rather than creating new ones. Object pools are often used to manage the lifecycle of expensive resources, such as database connections or threads.

# 14 Q&A

## Single point of failure require--> Redundancy and Replication
HA Architecture - Micro services 

**Redundancy**: the duplication of critical components or functions of a system with the intention of increasing the reliability of the system and to improve actual system performance. <br>
Widely used in DBMS, usually with a primary-replica relationship between the original and the copies. The primary server gets all the updates, which then ripple through to the replica servers.<br>

**Replication**: sharing information to ensure consistency between redundant resources (e.g. SW or HW), to improve reliability, fault-tolerance, or accessibility.<br>

**Highly Availability Mode**: improve reliability, fault-tolerance, or accessibility<br>
* Redundancy  - Active-passive	HA mode (remove the single point of failure and provides backup in case a crisis by failover)<br>
* Replication - Active-active		HA mode <br>

**Failover** 
(con: more hardware and additional complexity, the potential for loss of data)<br>
* Active-passive (master-slave failover, the passive is hot/cold standby)<br>
* Active-active (master-master failover)<br>

Need to ensure consistency <br>
Also provide a backup or spare functionality if needed in a crisis <br>

message queue to queue all requests, so that the system is highly available and open to updates while remaining the consistent at the same time<br>

**Redundancy** - describes the fact that you have more than one node/component/process in a system and it's pretty useful for handling failovers. In the case that one of your nodes fail, another node in the system can take over and carry on.<br> 
Redundancy can be:
* active - where all the traffic goes to all nodes at the same time<br>
* passive - where one node receive traffic and in the case of failure, a switch will be made to another node.<br>
"Redundancy is the duplication of nodes, in case of some of them are failing"<br>

**Replication** - includes redundancy, but involves the copying of data from one node to another or the synchronization of state between nodes. An example of where replication is done is at the databases or MQs level that forms a cluster.<br> 
Replication can be:
* active: each node receives each message in order to keep in sync with the rest of the nodes<br>
* passive: this is the leader-follower model, where the leader receives all the requests and then forwards them to the followers.<br>
"Replication is the synchronization of state between redundant nodes."<br>

**Redundancy** : Duplication of critical components (node, process) with the aim to achieve reliability. Redundancy helps avoid single-point failure. For instance, if we have two instances running and one of them fails then, then the system can switch over to another one.<br>

**Replication** : Sharing information to ensure consistency between redundant resources.

## Checkpointing <-- Fault Tolerance
Each server performs checkpointing periodically and dump a snapshot to all its data onto a remote server. This will ensure that if a sever dies down, another server can replace it by taking its data from the last snapshot. 

## Fault Tolerance -> Checkpointing, Load Balancer, Replication

## Asynchronism
pre-render massive framework dynamic content into static HTML files and store to Amazon S3 or content delivery network. This would make website super fast(handle millions of request per sec) 
A script would do this job and would be called by cronjob every hour. This was one way of doing asynchronism.<br>
If a user requests for a computation-intensive task, the front end of the website sends the job to the job queue and signals back to the user and lets the user browse the website meanwhile.<br> 
As soon as the frontend is signaled about “job is done”, the frontend notifies the user about it.<br>

## Extensibility 
Our service should be designed to in a modular way with the expectation that new functionality will be added to it.<br> 

Facebook System Design
https://www.youtube.com/watch?v=hykjbT5Z0oE&t=1041s

## Ranking
* Involves multiple advanced ranking and recommendation algorithms; it is a computationally intensive task
* Consist of big-data processing systems that might utilize specialized hardware like graphics processing units (GPUs) and tensor processing units (TPUs)
* Factor: a reference count, freshness, user's previous history, likes, dislikes, shares, comments, clicks, user location, language, personal history, demographics
* Consider all these factors to predict relevant and important posts for a user
* Select out a few top posts from a group of candidate posts based on the assigned scores
* Sort and display these selected posts in decreasing order of the assigned scores 

## Popular services: 
Distributed cache: Redis<br>
Search Index : Elastic<br>
Message queue : Kafka<br>
Databases NoSql : HBase<br>
Databases Relational: MySql<br>

## Interview tool
Facebook offered me three choices - Google Drawings,
BlueJeans Whiteboard, or ScreenShare your choice


## Questions: 
https://www.youtube.com/watch?v=hykjbT5Z0oE&list=PLCfguwhZH5DnHl2yldI781yR6FAgky0Np&index=1
1. Design Facebook NewsFeed - xx
2. Design Facebook Status Search - x
3. Design Live Commenting at Facebook
4. Design Facebook Messenger or WhatsApp - x
5. Design Instagram - x
https://www.youtube.com/watch?v=Hq8pZ8G2Lm8&t=652s
6. Design Proximity Server - x
7. Design Typeahead Suggestions - x
8. Design Top N Songs
9. Design Privacy Settings 
10. Design Web crawler - x

Dropbox - x

Design TinyURL - x
Design Uber - x
Design Twitter - x
Design Ticketmaster - x
Design an API rate limiter - x 
Design YouTube - x

# 15 Future + ML 
1. Use two demansions time and space for a topic. e.g. Netflex
2. Sychronize post by topics
3. Allow to take a deep dive into the particular topic. e.g. Netflex
4. Create an audio narrator based on AI + ML 
5. Offer the suggestion or possibility on true or false for the news/source
6. Provider both positive and negative on the same topic; can configure the percentage
7. Can follow up some topics a few days after first reviewing and get more new information about it

# 16 Review, Evaluate, and Evovle
Reviewing, evaluating, and evolving a system design is a crucial ongoing process to ensure that the design meets requirements, performs effectively, and can adapt to changing needs. Here's a step-by-step approach to achieve this:

1. **Initial Review**:
   - Conduct an initial review of the system design with stakeholders and team members to ensure alignment with requirements and goals.

2. **Peer Reviews**:
   - Engage in peer reviews where team members with diverse expertise examine the design for potential issues, inconsistencies, or improvements.

3. **Performance Evaluation**:
   - Test the system design with realistic workloads to assess its performance, scalability, and response times.
   - Identify potential bottlenecks, latency issues, or areas requiring optimization.

4. **Security Assessment**:
   - Evaluate the design's security mechanisms, authentication, authorization, and data protection strategies.
   - Conduct security audits and penetration testing to identify vulnerabilities.

5. **Scalability Test**:
   - Validate whether the system can handle increased load and user concurrency as intended.
   - Implement load testing to identify potential performance degradation under heavy traffic.

6. **User Acceptance Testing**:
   - Involve end-users or stakeholders to perform user acceptance testing.
   - Gather feedback on usability, functionality, and user experience.

7. **Feedback Incorporation**:
   - Incorporate feedback from various reviews, evaluations, and testing phases.
   - Address identified issues, revise design documents, and make necessary adjustments.

8. **Documentation Update**:
   - Keep design documentation up-to-date with any changes, improvements, or refinements.
   - Ensure that the documentation accurately represents the current state of the system.

9. **Evolution Planning**:
   - Anticipate future requirements and potential changes to the system.
   - Plan for how the system design can accommodate new features, technologies, and scalability needs.

10. **Technology Assessment**:
    - Regularly assess emerging technologies and frameworks that could enhance or replace components in the system.
    - Evaluate the impact of adopting new technologies on the overall architecture.

11. **Continuous Monitoring**:
    - Implement monitoring and logging to gather data on system performance and usage patterns.
    - Analyze this data to identify areas for optimization and improvements.

12. **Regular Review Cycles**:
    - Establish a regular cadence for design reviews and evaluations to ensure the system remains aligned with changing requirements and industry best practices.

13. **Feedback Loops**:
    - Maintain open channels of communication with users, stakeholders, and team members.
    - Use feedback loops to continuously gather insights and suggestions for enhancements.

14. **Iterative Improvement**:
    - Embrace an iterative approach to system design.
    - Continuously evolve the design to address issues, adapt to new needs, and incorporate lessons learned from previous iterations.

By following these steps, you can create a systematic process for reviewing, evaluating, and evolving your system design, leading to a more robust, effective, and adaptable solution over time.