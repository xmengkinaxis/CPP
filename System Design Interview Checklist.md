# System Design Interviews checklist

# 0. Time Allocation
1. understand the problem and establish design core: ~10 minutes (3 - 10 m)
2. Propose high-level design and get buy-in; -10 minutes (10 - 15 m)
3. Design deep dive; 20 minutes (10 - 25 m)
4. Wrap: 5 minutes (3 - 5 m)

# NOTE: 
The key aspect of system design is to identify the problem area and trade off, and be able to justify a decision over another. 
Get the skeleton in the place and then start optimizing (optimization is an evolutionary process) notch by notch;

* Lead and drive an Open-ended conversation as doing a demo or presentation;
* Everything is a trade-off; Make points with justification
* No single-point failure (to achieve highly reliable, no data lost)

# 1. Ask clarifying and high-level design Questions to scope the problem well
what an interviewer is expecting from us, 
	* to Gather requirements, and to scope the problem
	* to outline use cases, to gather constraints, and to validate our assumptions
Whenever you interact with a platform, think of the who, why, what, and how. Looking into designing the incentives for all kinds of users for them to interact with the system. 

## 1.1 Functional Requirements (Product Features + User Requirements)
What does the system do? 
What is the goal?
What are the inputs and outputs of the system?
// What is the criticality of the system?

Who is going to use it? How many kinds of users are there? The categories of people. E.g.Creator, Viewer, and Advertiser. 
Why? Their incentives to use the system. We develop the whats (incentives/procedures) and the whys (why someone would interact with that kind of content).
How are they going to use it? 
What are the use cases? 
What kind of operations does the system support?

## 1.2 Non-Functional Requirements (Product Properties + User Expectations) (PACELC + reliable + Scalability + Extensibility)
CAP theory. CP or AP? PACELC (When Partition, Availability or Consistency, Else Latency or Consistency); High reliable and high scalable; 
Reliability, Redundant, Stable, Security, Availability 100 up-time?, Simplicity vs Complexity, Maintainability, Consistency, or eventual consistency

Need enough resources to handle the increasing load; the system must be simple so that it is easy to scale at any point in time; performance should always be increased with scalability. 

### Availability: 
the percentage of the time that a system remains operational to perform its required function in a specific period under normal conditions; if a system is reliable, it is available. However, if it is available, it is not necessarily reliable.  
Every request received by a non-failing node in the system must result in a response. Refers to the system's ability to remain accessible even if one or more nodes in the system to go down. 
Measured in a number of 9s, three 9s - 99.9%, four 9s - 99.99%
Availability = Uptime ÷ (Uptime + downtime); 
Mean Time Between Failures (MTBF): total uptime / # of failures. This is the average time between failures. 
Mean Time to Repair (MTTR): total downtime / # of failures. This is the average time taken to recover from a failure.

### Consistency: 
All nodes see the same data at the same time, no matter users read/write from/to any node. Equivalent to having a single up-to-date copy of the data. is the agreement between multiple nodes in a distributed system to achieve a certain value.
Strong consistency: the data in all nodes is the same at any time; offers up-to-date data, but at the cost of high latency.
Weak consistency: no guarantee that all nodes have the same data at any time. 
Eventual consistency: ensure data of each node of the database get consistent eventually; offers low latency at the risk of returning stale data.

### Efficiency (Latency and throughput): 
Two standard measures of its efficiency are the response time(or latency) that denotes the delay to obtain the first item and the throughput (or bandwidth) with denotes the number of items delivered in a given time unit. (Metrics: Latency/Response Time, throughput/Bandwidth)
Response Time: the time difference between request and response
Latency: how long a system takes to transmit data from one point to another point in the system;
Throughput is the amount of work done by the system in a given particular time. 
Bandwidth is the maximum data that can be transferred on the different networks.
Request Per Second;

### Scalability: 
a distributed system can continuously evolve in order to support the growing amount of work; Horizontal (scaling out) vs Vertical Scaling (scaling up)
increase resources and performance with increasing load and traffic over the existing system without affecting the complexity and performance; need enough resources to handle the increasing load, for it would be increased at any point in time; should be simple and easy to scale; performance should always be increased with scalability
A system can be called scalable if adding more resources in the system results in performance increases. Performance is directly proportional to resources added. 

### Reliability: 
keep delivering its service even when on or several of its software or hardware components fail; achieve this through redundancy of both the software component and data, (and hardware); achieve such resilience with a cost in order to eliminate every single point of failure; <-> vulnerable, data lost; (resilient, no single point of failure) (authentication)

### Concurrency:
To maximize system's performance: high bandwidth and high throughput.

### Serviceability or Manageability (simplicity): 
is the simplicity and speed with which a a system can be repaired or maintained. The ease of diagnosing and understanding problems when they occur, ease of making updates or modifications, and how simple the system is to operate

## 1.3 Prioritize requirements
Break it down, to the most important, minimal features for your system.

## 1.4 Design Considerations (no do, or assumption)
No user authentication; 
get all or nothing, not a partial result; 
fairness
put some restriction to stop system abuse, e.g. limit the size of text or image or video
assumption: surge in traffic

# 2. Capacity Estimation and Constraints: Traffic, Storage, Network/Bandwidth, Memory(cache) Estimation.
What are the constraints?

Among which based on the read-heavy or write-heavy machine we can apply the 80–20 rule. 
if this is a read-heavy, estimate read throughput.
If a system is write-heavy then we need to estimate the Storage requirements per day, per year, and for 5–10 years.

// traffic is the user request from users to servers, storage is the user data or user-request data on disk, bandwidth is traffic from servers to users.
// memory is the cache capacity in order to improve the performance, esp. for read-heavy
// Estimation of the scale of the system, is helpful when we focus on scaling, partitioning, load balancing, and caching. 

## 2.1 Traffic in write/second, or read/second
total users; 
DAU(Daily active users)
active connections per minutes

How many requests per second/day do we expect?
Type: (read, write, search); fast reads, fast writes, or both?
Count: write and Read count in million per day
Ratio: write : read ratio; generally 5 : 1

How much will it grow each year?

## 2.2 Storage in TB or GB/year
Write: Write count * write size; e.g. 400M * 300B = 120GB/day
	Total files/write; 
	average file/write sizes; Limit on user input for each paste or a certain time (text amount, image size, user URL size) (not abuse)
Metadata: user information, metadata about these writes

Growth: Estimate in 5 or 10 years; Growth rate? e.g. 120GB * 365 days * 5 years = 200TB
Margin: to keep some margin, If never more than 70% or 80% of capacity; Assuming a 70% capacity model (we don't want to go above 70% of the total capacity of our storage system); 200TB / 80% = 250TB
Replication: replication for fault tolerance; e.g. 250TB * 2 = 500TB;
(500TB / 4T/server = 125 servers) (NOTE: too big for a single machine, so must be partitioned) (so is the cache)

## 2.3 Bandwidth in KB/s or MB/s
Ingress (upload): write count per second/minute * write average size
Egress (download, outgoing): read count per second/minute * write average size
Bandwidth will decide how to manage traffic and balance load between servers. ??? 

## 2.4 Memory (cache) in GB or TB /day
80-20 rule: 20% of hot pastes generate 80% of traffic, so only cache these 20% of pastes
20% of daily traffic and based on client's usage patterns, can adjust how many cache servers we need
20% * read count / per day * write average size 

Benefit: Low latency (real time)

# 3. System API design in CRUD (Create/paste/post, Read/get, Update/put, Delete)
The goal of the APIs is to make as much as clean & simple as possible to be simple to understand for everybody. A simple common way is making CRUDs.
Establish the exact contract expected from the system and ensure if we haven't gotten any requirements wrong. 
Remember to use always a key for secure authentication; throttle users based on their allocated quota.
Another consideration is to decide if our application will be Client Driver or Server Driver.
Another consideration how do we want to split our requests ???
SOAP or REST API

api_dev_key : the API developer key of a registered account. throttle users based on their allocated quota
Search Query: 
Maximum Results to Return: 
sort(number) Optional sort mode: 0 - latest first, 1 - best matched, 2 - most liked
page_token(string) specify a page in the result set that should be returned
Timestamp: 

Return: (JSON) a list of results matching the search query

# 4. Database Design
Benefit: Defining the data model in the early part of the interview will clarify how data will flow between different system components. Later, it will guide for data partitioning and management. 
Identify various system entities (primary objects), their relationship (static), how they will interact with each other (dynamic, create, extract, transform, load), and how these objects flow between different system components. 

Which database system should we use? NoSQL like Cassandra or MySQL?

## 4.1 Database Schema or components/classes and their relationship/connection (static)
What to store? objects, and their relations
Table, Relationship
Primary Key
Foreign Key 

Consideration for objects
1. Does store billions of records (objects)?
2. for each object, Is the object small (less than 1KB) or medium (a few MB, separated to object storage)?
3. What is the relationship between records?

Storage: 
Storage layer = Metadata storage + Object storage; such a division of data will allow us to scale them individually
Metadata storage: like users, pastes, etc. can use Relational DB like MySQL, or distributed key-value DB like Dynamo or Cassandra
Object Storage: like a text paste, an image, etc; use object storage like Amazon S3, or HDFS. 

Common objects (e.g.)
User: id (primary key, int), name (varchar 20), email (varchar 32), CreationDate (datetime, 4 byte?), LastLogin (datetime), Birthday (datetime)
Description (512 or 256), phone (12), path(256, path to the object storage)
item: CreationData, ExpirationDate, type (int), Description (varchar 512), Category: (smallint), UserId(int, creator), contents(varchar 256), Path(varchar 256)
location: latitude, longitude (int - 4 bytes, or 8 bytes)
num of likes/dislikes (int), num of comments, num of shares, num of views
Rating(how many stars a place gets out of ten)
Photo: PhotoID(int), UserID(int), PhotoPath(varchar 256), Photo Latitude & Longitude (int), User Latitude & Longitude (int), CreationDate(datetime)

tags: 
category: (1 byte)
default_language: 

latest (CreationDate), popular (likes, comments, shares), relevant (used in ranking)  

On which field(s) to build some index?
Pro: database performance =>  indexes to improve the performance of search queries, esp. when dataset is huge
Con: Dramatically speed up data retrieval, but slow down the write (insert, update, and delete) performance.

the goal of creating an index on a particular table in a database is to make it faster to search through the table and find the row or rows that we want. 
must carefully consider how users will access the data. 
Indexing needs a primary key on the table with a unique value; Using one or more columns
Ordered indexing (increasing or decreasing) or Hash-indexing
In any index-based data, the partition is not allowed ???

# 5. High-Level Design — This is pretty much a template, you can put in front of interviewers.
Outline a high level design with all important components and connections, involved in the request flow from the client until the response is passed to the client. 
Draw a block diagram with 5-6 core components of the system, which are enough to solve the actual problem from end to end.
The candidate should identify various system entities, how they will interact with each other. how data would be flowing in the system???

Map features to modules
Sketch the main components and connections
Justify your ideas

Structure/Components (static): 
Usually, a scalable system include (The Single Responsibility Principle advocates for small and autonomous services that work together to allow scale and configure them independently)
1. Load balancer
2 .WebServer (reverse proxy), 
3. Service (application layer, aka. platform layer) (Service Partition; list different services required) 
4. Caching system
5. Database (master/slave cluster)

NOTE: 
Application layer will process all incoming and outgoing requests. 

# 6. Low-Level Design - Design core components; detailed component design
Dig deeper into details of two or three major/core components;
Pick or ask for; The interviewers' feedback should always guide us to what specific parts need focus, elaborate on, and further discussion. 
(self choose some core components which are critical in performance)

Present different approaches, their pros and cons, and explain why we will prefer one approach over the other;  
Consider and Discuss potential solutions and trade-offs between different options while keeping system constrains in mind;

How to handle XXX (a write or a read) request? If failed (such duplicated key), how to handle?
pull vs push

reduce latency by prefetch/pre-calculate, caching, parallelization/Asynchronous loading
Customer behavior can be predicted, and heavy customer requests can be pre-calculated and saved using customer proxy pre-cache.

## 6.1 Scale the design 
purpose
Identify, address, and mitigate bottlenecks and single point of failures using principles of scalable system design.
1. Is there any single point of failure? a standby replica; Discuss as many bottlenecks as possible and different approaches to mitigate them
2. Identify and address bottlenecks, given the constraints.

approaches/methods
a. Load balancer (avoid dynamic overheated or static overloaded) - What components need better load balancing?
b. Caching - How much and at which layer should we introduce cache to speed thing up? 
c. Partition (horizontally scale, Database sharding); How to partition to distribute to multiple database (avoid uneven distribution [overloaded] and hotspot [overheated], user abuse behavior)
d. Replication - Define how the data will be replicated across servers
e. Index the database/tables ???

## 6.2 Partition and Replication (core of a distributed system, to scale out the system)
To mitigate the single point of failure and bottleneck: 
1. single point of failure: backup or failover (fault tolerance)
2. bottleneck: improve load balancing and performance by creating duplicates/replication
The new problem introduced by replication:
1. consistency

Replication: the duplication of critical components or functions of a system, in the form of a backup or fail-safe (for fault tolerance) or to improve actual system performance (for load balancing); make multiple copies of data and store them on different servers. sharing information must ensure consistency between redundant resources. remove the single points of failures and provide backups in a crisis. It improves the availability, durability, reliability of data across the system. It can achieve load balance and fault tolerance. e.g. Primary and secondary, primary-replica relationship
1. Keeping data geographically closer to the consumers of data
2. Tolerate failure in case some parts of the system fail.
3. Scale the number of machines that can serve read queries.

Partitioning (Horizontal or Vertical): the technique to break a big Database into many smaller parts, and the process of distributing/splitting up a database/table across a set of servers. So that each database can only manage a subset of the data. It is to improve the manageability, performance, scalability, availability (fault tolerance), and load balancing of an application; access only a smaller fraction of data to run a query faster as there is less data to scan; reduce the overall response time
Partitioning of relational data usually refers to decomposing your tables either row-wise (horizontally) or column-wise (vertically).
for higher efficiency and lower latencies

Scaling horizontally (or scaling out) means adding more instances of an application or service to share the load. conversely, scaling vertically (or scaling up) is about adding more resources, like CPU power or memory, to an instance. 

Pro: less read and write traffic, less replication, and more cache hit. Allow write in parallel with increase throughput. Index size is also reduced, which generally improve performance with faster queries. 

Method: 
1. Horizontal partitioning (range based partitioning, Data Sharding) put different rows into different tables: Pros: statically in a predictable manner; Cons: unbalanced servers or hotspots, higher latencies, and unavailability)
e.g. Key-based (Hash) sharding; Range-based Sharding; Directory-Based Sharding (Dynamic Sharding)(by using a lookup table if the number is fixed) 
1.1 Hash-based Partitioning -> overloaded partition -> Consistent Hashing; Pros:evenly and randomly distribution, minimize hotspot, speed up the rebalancing process after adding or removing nodes, easier for clusters with heterogeneous machines; Cons: need to ask all and then aggregate the results
1.2 Range, list, hash partitioning; and combined partitioning (partition, and sub-partition); (partition based on the maximum capacity of the server); Pro: static and a predictable manner; Con: unbalanced
1.3 Directory Based Partitioning: a loosely coupled approach; the lookup/dictionary server that holds the mappings between each tuple key to its DB server. Pros: changing without an impact on the application

Criteria: (hash, range, RR, composite)
a. Key or Hash-based partitioning; hash some key attributes of the storing entities to the partition number; consistent hashing to create a uniform distribution/allocation
b. List partitioning; each partition is assigned a list of (key) values (sometime, similar to a range based partitioning, sharding)
c. Round-robin partitioning
d. Composite partitioning; any combination of the above partitioning schemes to devise a new one

Rebalancing Reasons:
a. the distribution is not uniform (not evenly distributed)[overloaded]
b. a lot of load on a partition (hotspot)[overheated]
Method: 
a. Create more DB partitions; 
b. Rebalance existing partitions

2. Vertical partitioning: divide data to store tables (divide table to store its columns) related to a specific feature/need in their own servers: Pro: straightforward to implement and low impact on application; Con: additional growth->further partition, joining two tables in two separate Db can cause performance and consistency issues; 
Federation (functional partitioning) splits up databases by function, resulting in less read and write traffic to each database and therefore less replication lag; the database is smaller, easier to fit in memory and cache; write in parallel, increasing throughput.
Con: Update application logic to determine which database to read and write; join is more complex; more hardware and additional complexity. 

Problem: on a partitioned database, there are some extra constraints on the operations that can be performed, esp. operations that across multiple tables or multiple rows in the same table, but on different servers
a. join and denormalization(data inconsistency): perform a cross-partition query on a partitioned database is not feasible;
b. Referential integrity (application have to enforce this); enforcing data integrity constraints such as foreign keys in a partitioned database can be extremely difficult; Database does not support; application that require referential integrity on partitioned database often have to enforce it in application code; 
c. Rebalancing: data distribution is not uniform (uneven, unbalanced, overloaded/underloaded); a lot of load on a partition (hotspot); 

A large number of logical partitions to accommodate future data growth, vs a few physical database server. Such database server can have multiple database instances running on it. Use a configuration file to map the logical partitions to database server. So that can move partitions around easily. 
For better performance and scalability, we can keep more shard than these just required. 
Co-resident partitioning(on the same machine) is to reduce the size of individual indexes and reduce the amount of I/O (input/output) when updating records;
Remote partitioning is to increase the bandwidth of access to the data by having more RAM, avoiding disk access, have more network interface and disk I/O channels available. 

How to map a particular piece of data to its node? How to move and minimize data movement when adding or removing nodes? => consistent Hash. 

Other consideration: evenly distribute the load, no hotspot


# 7. Optimization

## 7.1. Security and Permissions
a. Privacy ???  
b. Security (certification and authentication)
c. Throttle (API rate limiting) (against abusive behaviors, misbehavior, spikiness in traffic) 
Rate Limiting is limiting the amount of operation that can be done in a limited amount of time. e.g. security ramification, performance ramification. It is a defensive measure for services, protect the system from flooding with the traffic, for denial of service (DOS)
d. International Law (e.g. restriction on video contents)

## 7.2. Analytics - users behavior 
Purpose: Get some insight on how users use the system 
a. Collect information on user behaviors from where ???
b. Analyze
c. Predict or forecast
d. Adjust based on the user's usage/login pattern (when and frequency)

logging request and response ???

## 7.3 Performance monitor - system performance (telemetry)
Purpose: Get an instant insight on how our system is doing (get an understanding of the performance of the service); address latency and throughput
Is the visibility to system health, system performance, and general statics; gather meaningful matrix (metrics/counters) and have tools to monitor these matrix;
a proper monitoring and logging system. 

a. Collect data constantly - which component do so?
How many are the actual daily active users? user locations, date and time of their access
When is the daily peak?
How is the average latency?

b. Alert when critical component fail or their performance degrade
c. Determine if we need more load balancing (scaling), or caching, or replication, or further partitioning. 

# Q&A

## 1. How to scale web servers (reverse proxy)? -> Load Balancers & its algorithms
LB helps to spread the traffic across a cluster of servers to improve overall responsiveness and availability of application, websites or databases, prevent a single point of failures, and keeps tracks of the status of all the resources; optimize resource usage (avoid overload and under-load of any machine); achieve maximum throughput; minimize response time
To utilize full scalability and redundancy, try to balance the load at each layer of the system;
faster, higher throughput, easier for administrators, predictive analytics to determine traffic bottlenecks, give actionable insights to automation and help drive business decisions.
LB helps scale horizontally across an ever-increasing number of servers.

metrics: active Connections (session affinity or sticky session), Latency, Bandwidth(throughput); random (Round Robin or Hash) 
algorithms: static [RR, weighted, IP hash], dynamic [LCM, LRM, LBM]
Least connection Method, LCM (servers with fewest active connections)
Least Response Time Method, LRM (servers with lowest average response time)
Least Bandwidth Method, LBM (lowest MB/s traffic)
Round Robin: does not take server load into consideration, RR; can overloaded
Weighted Round Robin Method, WRR
IP Hash (IP Address affinity)
Random : Simple to implement and no overhead
By request parameters

implemented with hardware (expensive) or with software.e.g HAProxy (layer 4 or 7), NGINX
Layer 4 - transport layer; source and destination IP, port
Layer 7 - application layer; header, message, cookies

Con: 
a. performance bottleneck, if it does not have enough resources or it is not configured properly
b. increase the complexity (be stateless, session can be stored in a centralized data store)
c, single point of failure

## 2. How to scale database? -> Caching or vertically and horizontally
Cache the DB results adding an extra caching layer between the servers and the database 
Cache will enable you to make vastly better use of the resources you already have as well as making otherwise unattainable product requirements feasible. 
Can exist at all levels in architecture, but are often found at the level nearest to the front end, where they are implemented to return data quickly without taxing downstream levels. 
Disadvantages: main consistency between caches and the source of truth (database) through cache invalidation which is difficult; need to make application changes

CDN (Content Delivery Network) are a kind of cache that comes into play for sites serving large amounts of static media. Can replicate content in multiple places, based on user's geographic location and the original of the webpage; security improvement, increase in content availability and redundancy, better load times, low bandwidth cost.  
type: Push and Pull, referring the data streaming upload and download???

Caching works well with static data by saving time and increasing speed, but not well with mutable or dynamic , for need to make sure that the cached data is in sync
What should be cached? long-running queries on databases; high-latency network requests (for external APIs), computation-intensive processing; 

A cache is a key-value store that reside between applications and data storage; 
Redis is persistent while memcache scales well.


### Cache eviction policies:
Policies: Order (first vs last), Recently (time: least vs most), Frequency (least), Random;
First In First Out (FIFO)
Last In First Out (LIFO)
Least Recently Used (LRU)
Most Recently Used (MRU)
Least Frequently Used (LFU)
Random Replacement (RR)

### Cache strategy (Invalidation): 
Cache Invalidation: keep the cache coherent with the source of data (e.g. database);  
strategy: cache and permanent story like disk or database, write only one or both; depend on the data and data access patterns (how data is written and read)  
metrics: read-intensive vs write-intensive (write-write, write-reread); latency and throughput; consistency and data loss;   

Cache aside: general purpose, work best for read-heavy workloads; usually write-around, use write-through or Time To Live(TTL) to invalidate cache in order to avoid the stale data; The application is responsible for reading and writing from the storage. The cache does not interact with storage directly. Application load the entry from database, add it to cache and then return it to user. Lazy loading. Only requested data is cached. 
Read-through
Write-through: data is written into both cache and database simultaneously. The application uses the cache as the main data store, reading and writing data to it, while the cache is responsible for reading and writing to the database synchronously. pros: fast retrieval, consistency between cache and storage, minimizes the risk of data loss; cons: higher latency for write operation; data written might never be read. 
Write-around: data is written into the permanent storage only (bypassing the cache). pros: cache is not flooded with written operation which is not subsequently be re-read. con: higher latency for the recently written data, for cache-miss, so higher latency;  
Write-back (write-behind): the data is written to cache alone; asynchronously write entry to the data store. pros: low-latency and high-throughput for write-intensive applications. con: risk of data loss; more complex to implement, for its asynchronously writing. 

## Scalability result ==> low-latency and fault-tolerant by replicate (deal with lower performance)
Scalability methods—With the architecture, there are many techniques and methods which can be used in order to customize and improve the design of a system. 
Some of the most widely used are: redundancy, partitioning, caching, indexing, load balancing, and queues.

## Shard result==> high performance by destructing the load and high available, and latency-free

## 3. How to prepare our assets to deliver faster across the world? -> CDNs

## real-time and low-latency require--> Replication of servers and server's location close to users (CDN) (PULL vs PUSH)
real-time (VOIP, video, notification system and real-time feeds) : push (message queue), not pull(expensive in bandwidth and unnecessary load on Servers and DB, not scalable)
The process of pushing a post to all the followers is called fanout. The push fanout is called fanout-on-write, while the pull fanout is called fanout-on-load. A combination of 'push to notify and 'pull for serving' 

use HTTP long polling or webSocket
(Normal/Periodical poll : have a delay on client , waste bandwidth, keep the server busy; client<-bandwidth->server)
Push can give a lot of improvement in latencies, throughput, and performances

News feed. 
Pull: Pro: mobile does not waste data plan, con: not real-time/in-time, most requests will result in an empty response
Push: need main a long poll request; Con: celebrity users who has millions of followers, the server pushes update too frequently
Hybrid: the users who have a high number of followers to a pull-based model and only push data to those who have a few hundred/thousand follows; or the server pushes update to all the users not more than a certain frequency and letting users with a lot of updates to pull data regularly

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

Redundancy - describes the fact that you have more than one node/component/process in a system and it's pretty useful for handling failovers. In the case that one of your nodes fail, another node in the system can take over and carry on. Redundancy can be:
active - where all the traffic goes to all nodes at the same time
passive - where one node receive traffic and in the case of failure, a switch will be made to another node.
"Redundancy is the duplication of nodes, in case of some of them are failing"

Replication - includes redundancy, but involves the copying of data from one node to another or the synchronization of state between nodes. An example of where replication is done is at the databases or MQs level that forms a cluster. Replication can be:
active: each node receives each message in order to keep in sync with the rest of the nodes
passive: this is the leader-follower model, where the leader receives all the requests and then forwards them to the followers.
"Replication is the synchronization of state between redundant nodes."

Redundancy : Duplication of critical components (node, process) with the aim to achieve reliability. Redundancy helps avoid single-point failure. For instance, if we have two instances running and one of them fails then, then the system can switch over to another one.

Replication : Sharing information to ensure consistency between redundant resources.

## Checkpointing <-- Fault Tolerance
Each server performs checkpointing periodically and dump a snapshot to all its data onto a remote server. This will ensure that if a sever dies down, another server can replace it by taking its data from the last snapshot. 

## Fault Tolerance -> Checkpointing, Load Balancer, Replication

## Asynchronism
pre-render massive framework dynamic content into static HTML files and store to Amazon S3 or content delivery network. This would make website super fast(handle millions of request per sec) 
A script would do this job and would be called by cronjob every hour. This was one way of doing asynchronism.
If a user requests for a computation-intensive task, the front end of the website sends the job to the job queue and signals back to the user and lets the user browse the website meanwhile. 
As soon as the frontend is signaled about “job is done”, the frontend notifies the user about it.

## Extensibility 
Our service should be designed to in a modular way with the expectation that new functionality will be added to it. 

Facebook System Design
https://www.youtube.com/watch?v=hykjbT5Z0oE&t=1041s

## Ranking
a reference count, freshness, user location, language, personal history, demographics


## trade-off 
Explore competing solutions, speak to all their major tradeoffs, and make intelligent decisions about how to balance each of those tradeoffs

Push vs Pull (or hybrid).e.g in notification, in CDN; (celebrity user) (online only); (not more than 10 from a single user to avoid spamming) in newsfeed 
Pull CDN: first client request is slower. Time-To-Live
Push CDN: full response to upload content to the servers and rewriting URLs to point to the servers
	Traffic: heavy traffic works well with Pull CDN.  less traffic works well with Push CDN; 
	Configuration: Pull CDN is easier to configure than Push CDN: 
	Content Update: Sites with higher no of frequent updates work well with PUll CDN

Partition 
	based on user ID or Tweet/Status ID or Hybrid or based on creation time or combination of tweet id and creation time
		User ID; can do transaction; con: hotspot/high latency, unbalanced/uneven/non-uniform distribution, unavailability of all of the user's data;  
		Tweet ID; dedicate two separate database instances (with a load balancer), one even-numbered IDs and the other odd-numbered, to generate auto-incrementing IDs; con: no able to do batch operation; 
		Tweet Creation Time
		Combination of Tweet ID and its Creation Time (Encode the creation time into Tweet Id, e.g. Epoch Second || auto incrementing sequence)				
	range-based or hash based 
Database: RDBM SQL vs NoSQL
CAP Availability vs Consistency; choose based on business requirements in case of network partition



## NOTE: 
Lead the conversation; 
Defend your design; 
Do NOT over-design or under-design; 

Distributed cache: Redis
Search Index : Elastic
Message queue : Kafka
Databases NoSql : HBase
Databases Relational: MySql

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