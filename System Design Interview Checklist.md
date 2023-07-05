# System Design Interviews checklist

- [System Design Interviews checklist](#system-design-interviews-checklist)
- [0. Time Allocation](#0-time-allocation)
- [NOTE:](#note)
- [1. Ask clarifying and high-level design Questions to scope the problem well](#1-ask-clarifying-and-high-level-design-questions-to-scope-the-problem-well)
	- [1.1 Functional Requirements (Product Features + User Requirements)](#11-functional-requirements-product-features--user-requirements)
	- [1.2 Non-Functional Requirements (Product Properties + User Expectations) (PACELC + reliable + Scalability + Extensibility)](#12-non-functional-requirements-product-properties--user-expectations-pacelc--reliable--scalability--extensibility)
		- [Availability:](#availability)
		- [Consistency:](#consistency)
		- [Efficiency (Latency and throughput):](#efficiency-latency-and-throughput)
		- [Scalability:](#scalability)
		- [Reliability:](#reliability)
		- [Concurrency:](#concurrency)
		- [Serviceability or Manageability (simplicity):](#serviceability-or-manageability-simplicity)
		- [Durability](#durability)
	- [1.3 Prioritize requirements](#13-prioritize-requirements)
	- [1.4 Design Considerations (no do, or assumption)](#14-design-considerations-no-do-or-assumption)
- [2. Capacity Estimation and Constraints: Traffic, Storage, Network/Bandwidth, Memory(cache) Estimation.](#2-capacity-estimation-and-constraints-traffic-storage-networkbandwidth-memorycache-estimation)
	- [2.1 Traffic in write/second, or read/second](#21-traffic-in-writesecond-or-readsecond)
	- [2.2 Storage in TB or GB/year](#22-storage-in-tb-or-gbyear)
	- [2.3 Bandwidth in KB/s or MB/s](#23-bandwidth-in-kbs-or-mbs)
	- [2.4 Memory (cache) in GB or TB /day](#24-memory-cache-in-gb-or-tb-day)
	- [2.5 Servers' capability](#25-servers-capability)
- [3. System API design](#3-system-api-design)
- [4. Database Design (Define Data Model)](#4-database-design-define-data-model)
	- [4.1 Database Schema or components/classes and their relationship/connection (static)](#41-database-schema-or-componentsclasses-and-their-relationshipconnection-static)
- [5. High-Level Design — This is pretty much a template, you can put in front of interviewers.](#5-high-level-design--this-is-pretty-much-a-template-you-can-put-in-front-of-interviewers)
- [6. Low-Level Design - Deep dive core components; detailed component design](#6-low-level-design---deep-dive-core-components-detailed-component-design)
	- [6.1 Scale the design](#61-scale-the-design)
	- [6.2 Partition and Replication (core of a distributed system, to scale out the system)](#62-partition-and-replication-core-of-a-distributed-system-to-scale-out-the-system)
- [7. Optimization](#7-optimization)
	- [7.1. Security and Permissions](#71-security-and-permissions)
	- [7.2. Analytics - users behavior](#72-analytics---users-behavior)
	- [7.3 Performance monitor - system performance (telemetry)](#73-performance-monitor---system-performance-telemetry)
- [Q\&A](#qa)
	- [1. How to scale web servers (reverse proxy)? -\> Load Balancers \& its algorithms](#1-how-to-scale-web-servers-reverse-proxy---load-balancers--its-algorithms)
	- [2. How to scale database? -\> Caching or vertically and horizontally](#2-how-to-scale-database---caching-or-vertically-and-horizontally)
		- [Cache eviction policies:](#cache-eviction-policies)
		- [Cache strategy (Invalidation):](#cache-strategy-invalidation)
	- [Scalability result ==\> low-latency and fault-tolerant by replicate (deal with lower performance)](#scalability-result--low-latency-and-fault-tolerant-by-replicate-deal-with-lower-performance)
	- [Shard result==\> high performance by destructing the load and high available, and latency-free](#shard-result-high-performance-by-destructing-the-load-and-high-available-and-latency-free)
	- [3. How to prepare our assets to deliver faster across the world? -\> CDNs](#3-how-to-prepare-our-assets-to-deliver-faster-across-the-world---cdns)
	- [real-time and low-latency require--\> Replication of servers and server's location close to users (CDN) (PULL vs PUSH)](#real-time-and-low-latency-require---replication-of-servers-and-servers-location-close-to-users-cdn-pull-vs-push)
		- [cache result==\> low latency, high throughput and high available (if db server is down for a while)](#cache-result-low-latency-high-throughput-and-high-available-if-db-server-is-down-for-a-while)
	- [Single point of failure require--\> Redundancy and Replication](#single-point-of-failure-require---redundancy-and-replication)
	- [Checkpointing \<-- Fault Tolerance](#checkpointing----fault-tolerance)
	- [Fault Tolerance -\> Checkpointing, Load Balancer, Replication](#fault-tolerance---checkpointing-load-balancer-replication)
	- [Asynchronism](#asynchronism)
	- [Extensibility](#extensibility)
	- [Ranking](#ranking)
	- [trade-off](#trade-off)
	- [Popular services:](#popular-services)
	- [Interview tool](#interview-tool)
	- [Questions:](#questions)


<!-- TOC -->

# 0. Time Allocation
1. understand the problem and establish design core: ~10 minutes (3 - 10 m)
2. Propose high-level design and get buy-in; -10 minutes (10 - 15 m)
3. Design deep dive; 20 minutes (10 - 25 m)
4. Wrap: 5 minutes (3 - 5 m)

# NOTE: 
The key aspect of system design is to identify the problem area and trade off, and be able to justify a decision over another. <br>
Get the skeleton in the place and then start optimizing (optimization is an evolutionary process) notch by notch; <br>
Interviewrs are more interested in your thought process throughout the interview than in your final design. The success heavily depends on your ability to communicate your thought process and hold a discussion (collaborate). <br>

* Lead and drive an Open-ended conversation as doing a demo or presentation;
* Everything is a trade-off; Make points with justification; Defend your design;
* Do NOT over-design or under-design;
* No single-point failure (to achieve highly reliable, no data lost)
* Identify potential bottlenecks and future problems (scale)
* Describe failover and impacts on users and Service Level Agreements (SLAs)
* Backup and disaster recovery
* Usage patterns, and security

# 1. Ask clarifying and high-level design Questions to scope the problem well
what an interviewer is expecting from us, 
	* to Gather requirements, and to scope the problem
	* to outline use cases, to gather constraints, and to validate our assumptions
Whenever you interact with a platform, think of the who, why, what, and how. Looking into designing the incentives for all kinds of users for them to interact with the system. 

## 1.1 Functional Requirements (Product Features + User Requirements)
What does the system do? <br>
What is the goal? <br>
What are the inputs and outputs of the system? <br>
// What is the criticality of the system? <br>

Who is going to use it? How many kinds of users are there? The categories of people. E.g.Creator, Viewer, and Advertiser.  <br>
Why? Their incentives to use the system. We develop the whats (incentives/procedures) and the whys (why someone would interact with that kind of content). <br>
How are they going to use it?  <br>
What are the use cases? <br>
What kind of operations does the system support? <br>

## 1.2 Non-Functional Requirements (Product Properties + User Expectations) (PACELC + reliable + Scalability + Extensibility)
CAP theory. CP or AP? PACELC (When Partition, Availability or Consistency, Else Latency or Consistency); High reliable and high scalable;  <br>
Reliability, Redundant, Stable, Security, Availability 100 up-time?, Simplicity vs Complexity, Maintainability, Consistency, or eventual consistency <br>

Need enough resources to handle the increasing load; the system must be simple so that it is easy to scale at any point in time; performance should always be increased with scalability. <br> 

### Availability: 
* the percentage of the time that a system remains operational to perform its required function in a specific period under normal conditions; if a system is reliable, it is available. However, if it is available, it is not necessarily reliable.  <br>
* Every request received by a non-failing node in the system must result in a response. Refers to the system's ability to remain accessible even if one or more nodes in the system to go down. 
* Measured in a number of 9s, three 9s - 99.9%, four 9s - 99.99% <br>
* Availability = Uptime ÷ (Uptime + downtime);  <br>
* **Mean Time Between Failures (MTBF)**: total uptime / # of failures. This is the average time between failures.  <br>
* **Mean Time to Repair (MTTR)**: total downtime / # of failures. This is the average time taken to recover from a failure. <br>
* Availability can be achieved through CDN (Cache), redundancy (replica), load balancing (distribute the requests only to the active healthy nodes) <br>

### Consistency: 
All nodes see the same data at the same time, no matter users read/write from/to any node. Equivalent to having a single up-to-date copy of the data. is the agreement between multiple nodes in a distributed system to achieve a certain value.
Strong consistency: the data in all nodes is the same at any time; offers up-to-date data, but at the cost of high latency.
Weak consistency: no guarantee that all nodes have the same data at any time. 
Eventual consistency: ensure data of each node of the database get consistent eventually; offers low latency at the risk of returning stale data.

### Efficiency (Latency and throughput): 
* Two standard measures of its efficiency are **the response time(or latency)** that denotes the delay to obtain the first item and **the throughput (or bandwidth)** with denotes the number of items delivered in a given time unit. (Metrics: Latency/Response Time, throughput/Bandwidth)
* **Response Time**: the time difference between request and response
* **Latency**: how long a system takes to transmit data from one point to another point in the system;
* **Throughput** is the amount of work done by the system in a given particular time. 
* **Bandwidth** is the maximum data that can be transferred on the different networks.
* Request Per Second;

### Scalability: 
* a distributed system can continuously evolve in order to support the growing amount of work; 
* increase resources and performance with increasing load and traffic over the existing system without affecting the complexity and performance; need enough resources to handle the increasing load, for it would be increased at any point in time; should be simple and easy to scale; performance should always be increased with scalability <br>
* A system can be called scalable if adding more resources in the system results in performance increases. Performance is directly proportional to resources added. <br>
* Horizontal (scaling out) vs Vertical Scaling (scaling up) <br>
* Scalability can be achieved through CDN (Cache which bring the content closer to user and remove the requirement of high bandwith), reading replicas <br> 

### Reliability: 
keep delivering its service even when on or several of its software or hardware components fail; achieve this through redundancy of both the software component and data, (and hardware); achieve such resilience with a cost in order to eliminate every single point of failure; <-> vulnerable, data lost; (resilient, no single point of failure) (authentication)

### Concurrency:
To maximize system's performance: high bandwidth and high throughput.

### Serviceability or Manageability (simplicity): 
is the simplicity and speed with which a a system can be repaired or maintained. The ease of diagnosing and understanding problems when they occur, ease of making updates or modifications, and how simple the system is to operate

### Durability
The data, once uploaded, shouldn't be lost unless users explicitly delete that data.

## 1.3 Prioritize requirements
Break it down, to the most important, minimal features for your system.

## 1.4 Design Considerations (no do, or assumption)
No user authentication or authorization; both are already completed <br>
get all or nothing, not a partial result;  <br>
fairness <br>
put some restriction to stop system abuse, e.g. limit the size of text or image or video, or add a rate limiter (prevent abuse behavior, provide a fair and reasonable use of the resource's capacity when sharing among many users, control the cost of operations and avoid excess costs) <br>
assumption: surge in traffic <br>

# 2. Capacity Estimation and Constraints: Traffic, Storage, Network/Bandwidth, Memory(cache) Estimation.
The estimation will be helpful later when focusing on scaling, partitioning, load balancing, and caching <br>
What are the constraints? <br>

Among which based on the read-heavy or write-heavy machine we can apply the 80–20 rule.  <br>
if this is a read-heavy, estimate read throughput. <br>
If a system is write-heavy then we need to estimate the Storage requirements per day, per year, and for 5–10 years. <br>

// traffic is the user request from users to servers, storage is the user data or user-request data on disk, bandwidth is traffic from servers to users. <br>
// memory is the cache capacity in order to improve the performance, esp. for read-heavy <br>
// Estimation of the scale of the system, is helpful when we focus on scaling, partitioning, load balancing, and caching.  <br>

## 2.1 Traffic in write/second, or read/second
**Total users** <br>
* DAU (Daily active users) <br>
* Active connections per minutes <br>

**How many requests per second/day do we expect?** <br>
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

# 3. System API design
**Goal:**<br>
The goal of the APIs is to make as much as clean & simple as possible to be simple to understand for everybody. A simple common way is making CRUDs. <br>
Establish the exact contract expected from the system and ensure if we haven't gotten any requirements wrong.  <br>

**Consideration:**<br>
Remember to use always a key for secure authentication; throttle users based on their allocated quota. <br>
Another consideration is to decide if our application will be Client Driver or Server Driver. <br>
Another consideration how do we want to split our requests ??? <br>
SOAP or REST API <br>

**Operations:** <br>
* CRUD (Create/paste/post, Read/get, Update/put, Delete) 
* Others (Search, list)
* these operations might work on different objects/levels/scopes
* Registration or authentication

**Parameters:** <br>
* api_dev_key : the API developer key of a registered account. throttle users based on their * allocated quota <br>
* Search Query:  <br>
* aximum Results to Return:  <br>
* sort(number) Optional sort mode: 0 - latest first, 1 - best matched, 2 - most liked <br>
* page_token(string) specify a page in the result set that should be returned <br>
* Timestamp:  <br>

**Return:** <br>
(JSON) a list of results matching the search query

# 4. Database Design (Define Data Model)
Benefit: Defining the data model in the early part of the interview will clarify how data will flow between different system components. Later, it will guide for data partitioning and management.  <br>
Identify various system **entities** (primary objects), their **relationship** (static), how they will **interact** with each other (dynamic, create, extract, transform, load), and how these objects **flow** between different system components.  <br>

Which database system should we use? NoSQL like Cassandra or MySQL?

## 4.1 Database Schema or components/classes and their relationship/connection (static)
What to store? objects, and their relations <br>
Table, Relationship <br>
Primary Key <br>
Foreign Key  <br>

Consideration for objects <br>
1. Does store billions of records (objects)? <br>
2. for each object, Is the object small (less than 1KB) or medium (a few MB, separated to object storage)? <br>
3. What is the relationship between records? <br>

Storage:  <br>
Storage layer = Metadata storage + Object storage; such a division of data will allow us to scale them individually <br>
Metadata storage: like users/accounts, pastes/blobs(pictures, videos, etc.), etc. can use Relational DB like MySQL, or distributed key-value DB like Dynamo or Cassandra <br>
Object Storage: like a text paste, an image, etc; use object storage like Amazon S3, or HDFS.  <br>

Common objects (e.g.) <br>
User: id (primary key, int), name (varchar 20), email (varchar 32), CreationDate (datetime, 4 byte?), LastLogin (datetime), Birthday (datetime) <br>
Description (512 or 256), phone (12), path(256, path to the object storage) <br>
item: CreationData, ExpirationDate, type (int), Description (varchar 512), Category: (smallint), UserId(int, creator), contents(varchar 256), Path(varchar 256) <br>
location: latitude, longitude (int - 4 bytes, or 8 bytes) <br>
num of likes/dislikes (int), num of comments, num of shares, num of views <br>
Rating(how many stars a place gets out of ten) <br>
Photo: PhotoID(int), UserID(int), PhotoPath(varchar 256), Photo Latitude & Longitude (int), User Latitude & Longitude (int), CreationDate(datetime) <br>

tags:  <br>
category: (1 byte) <br>
default_language:  <br>

latest (CreationDate), popular (likes, comments, shares), relevant (used in ranking)   <br>

On which field(s) to build some index? <br>
Pro: database performance =>  indexes to improve the performance of search queries, esp. when dataset is huge <br>
Con: Dramatically speed up data retrieval, but slow down the write (insert, update, and delete) performance. <br>

the goal of creating an index on a particular table in a database is to make it faster to search through the table and find the row or rows that we want.  <br>
must carefully consider how users will access the data.  <br>
Indexing needs a primary key on the table with a unique value; Using one or more columns <br>
Ordered indexing (increasing or decreasing) or Hash-indexing <br>
In any index-based data, the partition is not allowed ??? <br>

# 5. High-Level Design — This is pretty much a template, you can put in front of interviewers.
**Goal** 
* The candidate should identify various system entities, how they will interact with each other, and how data would be flowing in the system
* static: components, their relationship and connections
* dynamic: workflow, how these components interact with each other, event/time sequences
  
**Steps**
* Outline a high level design with all important components and connections, 
  * Draw a block diagram with 5-6 core components of the system, which are enough to solve the actual problem from end to end.
  * Map features to modules
  * Sketch the main components and connections
  * Justify your ideas
* involved in the request flow from the client until the response is passed to the client. Describe the workflow based on the required operations

**Structure/Components (static):** 
Usually, a scalable system include (The Single Responsibility Principle advocates for small and autonomous services that work together to allow scale and configure them independently)
1. Client
2. Load balancer
3. WebServer (reverse proxy), Front-end servers
4. Services (application layer, aka. platform layer) (Service Partition; list different services required, micro-services) 
5. Caching system
6. Database (master/slave cluster, partition and replication)
7. Rate limiter
8. Manager node: access privilege, console
9. Monitoring service

NOTE: 
Application layer will process all incoming and outgoing requests. 

# 6. Low-Level Design - Deep dive core components; detailed component design
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
To mitigate the single point of failure and bottleneck:  <br>
1. single point of failure: backup (snapshot periodically and add logs) or failover (fault tolerance)
2. bottleneck: improve load balancing and performance by creating duplicates/replication
3. consistency: The new problem introduced by replication

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
  * replicate accross data centers and regions
  * pro: the primary can continue its work even if all secondary node are down; 
  * con: written data might be lost if the primary node is down

**Data replication models** (dimension #2 leadership)
* Single leader or primary-secondary replication; appropriate for read-heavy and read resilient, but not for write-heavy; primary is the bottleneck and the single point of failure; 
* Multi-leader replication; conflict when concurrent writes on the same data on the leaders; avoid conflicts, last-write-wins, or custom logic to handle conflicts
* Peer-to-peer or leaderless replication; quorums to solve the write-write inconsistency; 

**Partitioning (Horizontal or Vertical):** the technique to break a big Database into many smaller parts, and the process of distributing/splitting up a database/table across a set of servers. So that each database can only manage a subset of the data. It is to improve the manageability, performance, scalability, availability (fault tolerance), and load balancing of an application; access only a smaller fraction of data to run a query faster as there is less data to scan; reduce the overall response time <br>
Partitioning of relational data usually refers to decomposing your tables either row-wise (horizontally) or column-wise (vertically). <br>
for higher efficiency and lower latencies <br>

**Scaling horizontally (or scaling out)** means adding more instances of an application or service to share the load. conversely, scaling vertically (or scaling up) is about adding more resources, like CPU power or memory, to an instance. 

**Pro:** less read and write traffic, less replication, and more cache hit. Allow write in parallel with increase throughput. Index size is also reduced, which generally improve performance with faster queries. 

**Method:** 
1. Horizontal partitioning (range based partitioning, Data Sharding) put different rows into different tables: Pros: statically in a predictable manner; Cons: unbalanced servers or hotspots, higher latencies, and unavailability)
e.g. Key-based (Hash) sharding; Range-based Sharding; Directory-Based Sharding (Dynamic Sharding)(by using a lookup table if the number is fixed) <br>
   * Hash-based Partitioning -> overloaded partition -> Consistent Hashing; Pros:evenly and randomly distribution, minimize hotspot, speed up the rebalancing process after adding or removing nodes, easier for clusters with heterogeneous machines; Cons: need to ask all and then aggregate the results
   * Range, list, hash partitioning; and combined partitioning (partition, and sub-partition); (partition based on the maximum capacity of the server); Pro: static and a predictable manner; Con: unbalanced
   * Directory Based Partitioning: a loosely coupled approach; the lookup/dictionary server that holds the mappings between each tuple key to its DB server. Pros: changing without an impact on the application

**Criteria:** (hash, range, RR, composite)
a. Key or Hash-based partitioning; hash some key attributes of the storing entities to the partition number; consistent hashing to create a uniform distribution/allocation
b. List partitioning; each partition is assigned a list of (key) values (sometime, similar to a range based partitioning, sharding)
c. Round-robin partitioning
d. Composite partitioning; any combination of the above partitioning schemes to devise a new one

**Rebalancing Reasons:** <br>
a. the distribution is not uniform (not evenly distributed)[overloaded] <br>
b. a lot of load on a partition (hotspot)[overheated] <br>
Method: <br>
a. Create more DB partitions; <br>
b. Rebalance existing partitions <br>

1. Vertical partitioning: manually partition; divide data to store tables (divide table to store its columns) related to a specific feature/need in their own servers: Pro: straightforward to implement and low impact on application; Con: additional growth->further partition, joining two tables in two separate Db can cause performance and consistency issues;  <br>
Federation (functional partitioning) splits up databases by function, resulting in less read and write traffic to each database and therefore less replication lag; the database is smaller, easier to fit in memory and cache; write in parallel, increasing throughput. <br>
Con: Update application logic to determine which database to read and write; join is more complex; more hardware and additional complexity.  <br>

Problem: on a partitioned database, there are some extra constraints on the operations that can be performed, esp. operations that across multiple tables or multiple rows in the same table, but on different servers <br>
a. join and denormalization(data inconsistency): perform a cross-partition query on a partitioned database is not feasible; <br>
b. Referential integrity (application have to enforce this); enforcing data integrity constraints such as foreign keys in a partitioned database can be extremely difficult; Database does not support; application that require referential integrity on partitioned database often have to enforce it in application code; <br> 
c. Rebalancing: data distribution is not uniform (uneven, unbalanced, overloaded/underloaded); a lot of load on a partition (hotspot); <br> 

A large number of logical partitions to accommodate future data growth, vs a few physical database server. Such database server can have multiple database instances running on it. Use a configuration file to map the logical partitions to database server. So that can move partitions around easily.  <br>
For better performance and scalability, we can keep more shard than these just required.  <br>
Co-resident partitioning(on the same machine) is to reduce the size of individual indexes and reduce the amount of I/O (input/output) when updating records; <br>
Remote partitioning is to increase the bandwidth of access to the data by having more RAM, avoiding disk access, have more network interface and disk I/O channels available.  <br>

How to map a particular piece of data to its node? How to move and minimize data movement when adding or removing nodes? => consistent Hash. 

Other consideration: evenly distribute the load, no hotspot


# 7. Optimization

## 7.1. Security and Permissions
1. Privacy ???  
2. Security (certification and authentication)
3. Throttle (API rate limiting) (against abusive behaviors, misbehavior, spikiness in traffic) 
	* Rate Limiting is limiting the amount of operation that can be done in a limited amount of time. e.g. security ramification, performance ramification. 
	* It is a defensive measure for services, protect the system from flooding with the traffic, for denial of service (DOS)
	* types: Hard throttling (hard limit, discard when exceed), Soft throttling (can exceed by a certain percentage), Elastic or dynamic throttling (can cross the predefined limit if the system has excess resources available)
4. International Law (e.g. restriction on video contents)

## 7.2. Analytics - users behavior 
Purpose: Get some insight on how users use the system 
a. Collect information on user behaviors from where ???
b. Analyze
c. Predict or forecast
d. Adjust based on the user's usage/login pattern (when and frequency)

logging request and response ???

## 7.3 Performance monitor - system performance (telemetry)
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

# Q&A

## 1. How to scale web servers (reverse proxy)? -> Load Balancers & its algorithms
LB helps to spread the traffic across a cluster of servers to improve overall responsiveness and availability of application, websites or databases, prevent a single point of failures, and keeps tracks of the status of all the resources; optimize resource usage (avoid overload and under-load of any machine); achieve maximum throughput; minimize response time<br>
To utilize full scalability and redundancy, try to balance the load at each layer of the system;<br>
faster, higher throughput, easier for administrators, predictive analytics to determine traffic bottlenecks, give actionable insights to automation and help drive business decisions.
LB helps scale horizontally across an ever-increasing number of servers.<br>

metrics: 
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

algorithms: 
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

## 2. How to scale database? -> Caching or vertically and horizontally
Cache the DB results adding an extra caching layer between the servers and the database <br>
Cache will enable you to make vastly better use of the resources you already have as well as making otherwise unattainable product requirements feasible. <br>
Can exist at all levels in architecture, but are often found at the level nearest to the front end, where they are implemented to return data quickly without taxing downstream levels. <br>
Disadvantages: main consistency between caches and the source of truth (database) through cache invalidation which is difficult; need to make application changes<br>

CDN (Content Delivery Network) are a kind of cache that comes into play for sites serving large amounts of static media. Can replicate content in multiple places, based on user's geographic location and the original of the webpage; security improvement, increase in content availability and redundancy, better load times, low bandwidth cost.  <br>
type: Push and Pull, referring the data streaming upload and download???<br>

Caching works well with static data by saving time and increasing speed, but not well with mutable or dynamic , for need to make sure that the cached data is in sync<br>
What should be cached? long-running queries on databases; high-latency network requests (for external APIs), computation-intensive processing; <br>

A cache is a key-value store that reside between applications and data storage; 
Redis is persistent while memcache scales well.


### Cache eviction policies:
Policies: Order (first vs last), Recently (time: least vs most), Frequency (least), Random;<br>
First In First Out (FIFO)<br>
Last In First Out (LIFO)<br>
Least Recently Used (LRU)<br>
Most Recently Used (MRU)<br>
Least Frequently Used (LFU)<br>
Random Replacement (RR)<br>

### Cache strategy (Invalidation): 
Cache Invalidation: keep the cache coherent with the source of data (e.g. database);  <br>
strategy: cache and permanent story like disk or database, write only one or both; depend on the data and data access patterns (how data is written and read)  <br>
metrics: read-intensive vs write-intensive (write-write, write-reread); latency and throughput; consistency and data loss;<br>   

* Cache aside: general purpose, work best for read-heavy workloads; usually write-around, use write-through or Time To Live(TTL) to invalidate cache in order to avoid the stale data; The application is responsible for reading and writing from the storage. The cache does not interact with storage directly. Application load the entry from database, add it to cache and then return it to user. Lazy loading. Only requested data is cached.<br>   
* Read-through  <br>
* Write-through (both): data is written into both cache and database simultaneously. The application uses the cache as the main data store, reading and writing data to it, while the cache is responsible for reading and writing to the database synchronously. pros: fast retrieval, consistency between cache and storage, minimizes the risk of data loss; cons: higher latency for write operation; data written might never be read.   <br>
* Write-around (storage only): data is written into the permanent storage only (bypassing the cache). pros: cache is not flooded with written operation which is not subsequently be re-read. con: higher latency for the recently written data, for cache-miss, so higher latency; <br>   
* Write-back (write-behind)(cache only): the data is written to cache alone; asynchronously write entry to the data store. pros: low-latency and high-throughput for write-intensive applications. con: risk of data loss; more complex to implement, for its asynchronously writing.  <br> 

## Scalability result ==> low-latency and fault-tolerant by replicate (deal with lower performance)
Scalability methods—With the architecture, there are many techniques and methods which can be used in order to customize and improve the design of a system.<br> 
Some of the most widely used are: redundancy, partitioning, caching, indexing, load balancing, and queues.<br>

## Shard result==> high performance by destructing the load and high available, and latency-free

## 3. How to prepare our assets to deliver faster across the world? -> CDNs

## real-time and low-latency require--> Replication of servers and server's location close to users (CDN) (PULL vs PUSH)
real-time (VOIP, video, notification system and real-time feeds) : push (message queue), not pull(expensive in bandwidth and unnecessary load on Servers and DB, not scalable)
The process of pushing a post to all the followers is called fanout. The push fanout is called fanout-on-write, while the pull fanout is called fanout-on-load. A combination of 'push to notify and 'pull for serving' <br>

use HTTP long polling or webSocket<br>
(Normal/Periodical poll : have a delay on client , waste bandwidth, keep the server busy; client<-bandwidth->server)<br>
Push can give a lot of improvement in latencies, throughput, and performances<br>

News feed.<br> 
Pull: Pro: mobile does not waste data plan, con: not real-time/in-time, most requests will result in an empty response<br>
Push: need main a long poll request; Con: celebrity users who has millions of followers, the server pushes update too frequently<br>
Hybrid: the users who have a high number of followers to a pull-based model and only push data to those who have a few hundred/thousand follows; or the server pushes update to all the users not more than a certain frequency and letting users with a lot of updates to pull data regularly<br>

### cache result==> low latency, high throughput and high available (if db server is down for a while)
caching will enable you to make vastly better use of the resources you already have; 
application caching, database caching (need tweaking the configuration), in-memory caches

In-memory caches: 
precalculated results, pre-generating expensive indexes, storing copies of frequently accessed data in a faster backend

## Single point of failure require--> Redundancy and Replication
HA Architecture - Micro services 

Redundancy: the duplication of critical components or functions of a system with the intention of increasing the reliability of the system and to improve actual system performance. 
Widely used in DBMS, usually with a primary-replica relationship between the original and the copies. The primary server gets all the updates, which then ripple through to the replica servers.

Replication: sharing information to ensure consistency between redundant resources (e.g. SW or HW), to improve reliability, fault-tolerance, or accessibility.

Highly Availability Mode: improve reliability, fault-tolerance, or accessibility
Redundancy  - Active-passive	HA mode (remove the single point of failure and provides backup in case a crisis by failover)
Replication - Active-active		HA mode 
Failover 
(con: more hardware and additional complexity, the potential for loss of data)
a. Active-passive (master-slave failover, the passive is hot/cold standby)
b. Active-active (master-master failover)

Need to ensure consistency
Also provide a backup or spare functionality if needed in a crisis

message queue to queue all requests, so that the system is highly available and open to updates while remaining the consistent at the same time

Redundancy - describes the fact that you have more than one node/component/process in a system and it's pretty useful for handling failovers. In the case that one of your nodes fail, another node in the system can take over and carry on.<br> Redundancy can be:
active - where all the traffic goes to all nodes at the same time<br>
passive - where one node receive traffic and in the case of failure, a switch will be made to another node.<br>
"Redundancy is the duplication of nodes, in case of some of them are failing"<br>

Replication - includes redundancy, but involves the copying of data from one node to another or the synchronization of state between nodes. An example of where replication is done is at the databases or MQs level that forms a cluster.<br> Replication can be:
active: each node receives each message in order to keep in sync with the rest of the nodes<br>
passive: this is the leader-follower model, where the leader receives all the requests and then forwards them to the followers.<br>
"Replication is the synchronization of state between redundant nodes."<br>

Redundancy : Duplication of critical components (node, process) with the aim to achieve reliability. Redundancy helps avoid single-point failure. For instance, if we have two instances running and one of them fails then, then the system can switch over to another one.<br>

Replication : Sharing information to ensure consistency between redundant resources.

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
a reference count, freshness, user location, language, personal history, demographics


## trade-off 
Explore competing solutions, speak to all their major tradeoffs, and make intelligent decisions about how to balance each of those tradeoffs

* Push vs Pull (or hybrid).e.g in notification, in CDN; (celebrity user) (online only); (not more than 10 from a single user to avoid spamming) in newsfeed 
* Pull CDN: first client request is slower. Time-To-Live; suitable for serving dynamic content; favored for frequently changing content and a high traffic load; low storage consumption
* Push CDN: full response to upload content to the servers and rewriting URLs to point to the servers; appropriate for static content delivery; need more replicas than pull CDN
	* Traffic: heavy traffic works well with Pull CDN.  less traffic works well with Push CDN; 
	* Configuration: Pull CDN is easier to configure than Push CDN: 
	* Content Update: Sites with higher no of frequent updates work well with Pull CDN

* Partition 
	* based on user ID or Tweet/Status ID or Hybrid or based on creation time or combination of tweet id and creation time
		* User ID; can do transaction; con: hotspot/high latency, unbalanced/uneven/non-uniform distribution, unavailability of all of the user's data;  
		* Tweet ID; dedicate two separate database instances (with a load balancer), one even-numbered IDs and the other odd-numbered, to generate auto-incrementing IDs; con: no able to do batch operation; 
		* Tweet Creation Time
		* Combination of Tweet ID and its Creation Time (Encode the creation time into Tweet Id, e.g. Epoch Second || auto incrementing sequence)				
	* range-based or hash based 
* Database: RDBM SQL vs NoSQL
* CAP Availability vs Consistency; choose based on business requirements in case of network partition



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
1. Design Facebook NewsFeed - x
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