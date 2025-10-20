# System Design Interviews checklist

- [System Design Interviews checklist](#system-design-interviews-checklist)
  - [0 Interview Preparation](#0-interview-preparation)
    - [0.1 Time Allocation](#01-time-allocation)
    - [0.2 Tips on the process](#02-tips-on-the-process)
    - [0.3 Communicate through process](#03-communicate-through-process)
    - [0.4 Goal and Purpose](#04-goal-and-purpose)
    - [0.5 Expectations](#05-expectations)
    - [0.6 Should do](#06-should-do)
  - [1 Ask clarifying and high-level design questions to **scope** the problem well](#1-ask-clarifying-and-high-level-design-questions-to-scope-the-problem-well)
    - [1.1 Functional Requirements (Product Features/Functionalities + User Requirements)](#11-functional-requirements-product-featuresfunctionalities--user-requirements)
      - [1.1.1 Product Features/Functionalities](#111-product-featuresfunctionalities)
      - [1.1.2 User requirements](#112-user-requirements)
    - [1.2 Non-Functional Requirements (Product Properties + User Expectations in term of performance) (PACELC + Reliable + Scalability + Extensibility)](#12-non-functional-requirements-product-properties--user-expectations-in-term-of-performance-pacelc--reliable--scalability--extensibility)
      - [Availability](#availability)
      - [Reliability](#reliability)
      - [Efficiency/Performance (Latency and Throughput)](#efficiencyperformance-latency-and-throughput)
      - [Scalability](#scalability)
      - [Consistency](#consistency)
      - [Concurrency](#concurrency)
      - [Serviceability or Manageability (simplicity)](#serviceability-or-manageability-simplicity)
      - [Durability](#durability)
      - [Security](#security)
    - [1.3 Achieve NFR (Non Functional Requirement)](#13-achieve-nfr-non-functional-requirement)
    - [1.4 Prioritize requirements](#14-prioritize-requirements)
    - [1.5 Design Considerations (no do, or assumption)](#15-design-considerations-no-do-or-assumption)
  - [2 Capacity Estimation and Constraints: Traffic, Storage, Network/Bandwidth, Memory(cache) Estimation](#2-capacity-estimation-and-constraints-traffic-storage-networkbandwidth-memorycache-estimation)
    - [2.0 The common data used in estimation (TODO from Meta system design post???)](#20-the-common-data-used-in-estimation-todo-from-meta-system-design-post)
    - [2.1 Traffic in write/second, or read/second](#21-traffic-in-writesecond-or-readsecond)
      - [**Users**](#users)
      - [**Requests:** How many requests per second/day do we expect?](#requests-how-many-requests-per-secondday-do-we-expect)
    - [2.2 Storage in TB or GB/year](#22-storage-in-tb-or-gbyear)
    - [2.3 Bandwidth in KB/s or MB/s](#23-bandwidth-in-kbs-or-mbs)
    - [2.4 Memory (cache) in GB or TB /day](#24-memory-cache-in-gb-or-tb-day)
    - [2.5 Modern Server Capability](#25-modern-server-capability)
      - [⚙️ Modern-Day Server (Ballpark Capacity for Estimation)](#️-modern-day-server-ballpark-capacity-for-estimation)
      - [⚡ Practical Constants for Quick Estimation](#-practical-constants-for-quick-estimation)
  - [3 System API design](#3-system-api-design)
  - [4 Database Design (Define Data Model and Choose Database)](#4-database-design-define-data-model-and-choose-database)
    - [4.0 Data Model](#40-data-model)
    - [4.1 Database Schema or components/classes and their relationship/connection (static)](#41-database-schema-or-componentsclasses-and-their-relationshipconnection-static)
    - [4.2 Choose Database](#42-choose-database)
      - [Key Factors to Consider](#key-factors-to-consider)
      - [Database Options](#database-options)
      - [Hybrid Approach (Polyglot Persistence)](#hybrid-approach-polyglot-persistence)
  - [5 High-Level Design — This is pretty much a template, you can put in front of interviewers](#5-high-level-design--this-is-pretty-much-a-template-you-can-put-in-front-of-interviewers)
  - [6 Low-Level Design (LLD) - Deep Dive into Core Components (Detailed Component Design)](#6-low-level-design-lld---deep-dive-into-core-components-detailed-component-design)
    - [6.0 LLD Deep Dive Lenses: short checklists for common components to deep dive](#60-lld-deep-dive-lenses-short-checklists-for-common-components-to-deep-dive)
    - [6.1 Scale the design](#61-scale-the-design)
      - [6.1.1 Purpose](#611-purpose)
      - [6.1.2 Approaches / Methods](#612-approaches--methods)
      - [6.1.3 Interview Strategy](#613-interview-strategy)
    - [6.2 Partition and Replication](#62-partition-and-replication)
      - [6.2.1 Replication](#621-replication)
      - [6.2.2 Partition](#622-partition)
        - [6.2.2.1 Horizontal Partitioning (Sharding)](#6221-horizontal-partitioning-sharding)
        - [6.2.2.2 Vertical Partitioning](#6222-vertical-partitioning)
        - [6.2.2.3 Horizontal vs Vertical Partitioning](#6223-horizontal-vs-vertical-partitioning)
    - [6.3 Partitioning VS Sharding](#63-partitioning-vs-sharding)
      - [6.3.1 Partitioning](#631-partitioning)
      - [6.3.2 Sharding](#632-sharding)
      - [6.3.3 Key Differences (Quick Recall)](#633-key-differences-quick-recall)
      - [6.3.4 Comparison: Partitioning vs. Sharding](#634-comparison-partitioning-vs-sharding)
  - [7 Evaluation and Optimization](#7-evaluation-and-optimization)
    - [7.1 Evaluation](#71-evaluation)
    - [7.2 Security and Permissions](#72-security-and-permissions)
    - [7.3 Analytics (User Behavior)](#73-analytics-user-behavior)
    - [7.4 Monitoring and Telemetry](#74-monitoring-and-telemetry)
    - [7.5 Bottleneck Identification and Mitigation](#75-bottleneck-identification-and-mitigation)
    - [7.6 **Sample Wrap-up Answer (concise, interview-style):** 2–3 minute spoken version](#76-sample-wrap-up-answer-concise-interview-style-23-minute-spoken-version)
    - [7.7 **1-Minute Wrap-up Answer:**](#77-1-minute-wrap-up-answer)
    - [7.8 Words in Interview](#78-words-in-interview)
  - [8 Trade-off](#8-trade-off)
    - [8.1 Common Trade-offs](#81-common-trade-offs)
    - [8.2 Partitioning Trade-offs](#82-partitioning-trade-offs)
    - [8.3 User Connections: HTTP vs WebSocket](#83-user-connections-http-vs-websocket)
    - [8.4 CDN: Push vs Pull](#84-cdn-push-vs-pull)
    - [8.5 Newsfeed: Push vs Pull (Fanout Models)](#85-newsfeed-push-vs-pull-fanout-models)
  - [9 System Design Principles](#9-system-design-principles)
    - [9.1 Prioritized System Design Principles (for large-scale/distributed systems)](#91-prioritized-system-design-principles-for-large-scaledistributed-systems)
    - [9.2 Inaccurate Principles (Most are OOD in fact)](#92-inaccurate-principles-most-are-ood-in-fact)
  - [10 System Design Best Practices](#10-system-design-best-practices)
  - [11 Scale](#11-scale)
    - [11.1 Load Balancers \& its algorithms - How to scale web servers (reverse proxy)](#111-load-balancers--its-algorithms---how-to-scale-web-servers-reverse-proxy)
      - [Metrics](#metrics)
      - [Algorithm Categories](#algorithm-categories)
      - [algorithms](#algorithms)
    - [11.2 Caching - How to scale database?  Caching or vertically and horizontally](#112-caching---how-to-scale-database--caching-or-vertically-and-horizontally)
      - [Cache eviction policies](#cache-eviction-policies)
      - [Cache expiration](#cache-expiration)
      - [Cache strategy (Invalidation)](#cache-strategy-invalidation)
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
    - [Automation: The Self-Healing System](#automation-the-self-healing-system)
    - [Others](#others)
  - [13 Common Design patterns](#13-common-design-patterns)
    - [13.1 Microservices](#131-microservices)
    - [13.2 Event Sourcing](#132-event-sourcing)
    - [13.3 CQRS (Command Query Responsibility Segregation)](#133-cqrs-command-query-responsibility-segregation)
    - [13.4 Circuit Breaker](#134-circuit-breaker)
    - [13.5 Backpressure](#135-backpressure)
  - [14 Q\&A](#14-qa)
    - [Single point of failure require--\> Redundancy and Replication](#single-point-of-failure-require---redundancy-and-replication)
    - [Checkpointing \<-- Fault Tolerance](#checkpointing----fault-tolerance)
    - [Fault Tolerance -\> Checkpointing, Load Balancer, Replication](#fault-tolerance---checkpointing-load-balancer-replication)
    - [Asynchronism](#asynchronism)
    - [Extensibility](#extensibility)
    - [Ranking](#ranking)
    - [Recommendation](#recommendation)
    - [Popular services:](#popular-services)
    - [Interview tool](#interview-tool)
    - [Questions:](#questions)
  - [15 Future + ML](#15-future--ml)
  - [16 Review, Evaluate, and Evolve](#16-review-evaluate-and-evolve)
  - [17 Interview Framework](#17-interview-framework)
    - [17.1 Framework](#171-framework)
    - [17.2 Strategy for NFR](#172-strategy-for-nfr)
    - [17.3 API Gateway](#173-api-gateway)
    - [17.4 Common Single Points of Failure (SPOFs)](#174-common-single-points-of-failure-spofs)
    - [17.5 Common Bottlenecks](#175-common-bottlenecks)
    - [17.6 Mitigation SPOFs and addressing bottlenecks involves](#176-mitigation-spofs-and-addressing-bottlenecks-involves)
    - [17.7 Suggested Prioritization (for a 45-min interview)](#177-suggested-prioritization-for-a-45-min-interview)
  - [18 Terms](#18-terms)
    - [**API Gateway**](#api-gateway)
      - [Why it’s useful:](#why-its-useful)
      - [Common Features of API Gateway:](#common-features-of-api-gateway)
      - [Examples:](#examples)
      - [✅ Pros of API Gateway](#-pros-of-api-gateway)
      - [❌ Cons of API Gateway](#-cons-of-api-gateway)
      - [**When do you need a Load Balancer with an API Gateway?**](#when-do-you-need-a-load-balancer-with-an-api-gateway)
      - [**Connection Setup (Typical Flow)**](#connection-setup-typical-flow)
      - [**Key Notes for Interviews**](#key-notes-for-interviews)
    - [**Example: AWS Setup with API Gateway + Load Balancer**](#example-aws-setup-with-api-gateway--load-balancer)
      - [**Scenario**](#scenario)
      - [**Architecture Flow**](#architecture-flow)
      - [**Why Both?**](#why-both)
      - [**In an Interview, You Can Say:**](#in-an-interview-you-can-say)
      - [**1. Web Server / Reverse Proxy (Nginx, Envoy, HAProxy)**](#1-web-server--reverse-proxy-nginx-envoy-haproxy)
      - [**2. WebSockets for Real-Time**](#2-websockets-for-real-time)
      - [**3. API Gateway (if multiple services)**](#3-api-gateway-if-multiple-services)
      - [✅ So, can API Gateway replace Web Server + WebSocket?](#-so-can-api-gateway-replace-web-server--websocket)
      - [🔑 In your note, I’d refine it like this:](#-in-your-note-id-refine-it-like-this)
    - [Single Point of Failure (SPOF) vs Bottleneck](#single-point-of-failure-spof-vs-bottleneck)
      - [🔹 **Single Point of Failure (SPOF)**](#-single-point-of-failure-spof)
      - [🔹 **Bottleneck**](#-bottleneck)
      - [🔹 **Key Differences**](#-key-differences)
      - [🎯 System Design Interview Priority](#-system-design-interview-priority)
      - [🔑 Rule of Thumb for Interviews](#-rule-of-thumb-for-interviews)


<!-- TOC -->

## 0 Interview Preparation

### 0.1 Time Allocation

Clarify the problem, break down the complex problem into parts, discuss the overall design, and deep dive into some components; identify and analyze the tradeoffs, recover from the failures;

1. Understand the problem and establish design core: ~10 minutes (3 - 10 m)
2. Propose high-level design and get buy-in; -10 minutes (10 - 15 m)
3. Design deep dive; 20 minutes (10 - 25 m)
4. Wrap / Evaluation / feedback / discussion / question : 5 minutes (3 - 5 m)

### 0.2 Tips on the process

1. Manage your **time** efficiently
2. Discuss **trade-offs** with your interviewers
3. Start wide and end deep

### 0.3 Communicate through process

1. Start with the problem statement: clearly explain the problem and the requirements for the system; then explain your approach and how you plan to tackle the problem
2. Break down the problem: divide the problem into smaller parts and explain how you will solve each part individually
3. Use diagrams and sketches to help explain your design
4. Explain the **trade-offs** you made and the **constraints** you considered; demonstrate your ability to make informed (trade-off) decisions and your understanding of the problem (constraints)
5. Explain your reasoning: clearly explain why you made certain design decisions and how they address the problem and requirements; how you arrived at your solution
6. Be prepared to answer questions and provide alternatives with pros and cons
7. Be open to feedback: be prepared to revise your design based on feedback from the interviewer. This will demonstrate your ability to iterate and improve your design based on feedback.

Demonstrate your ability to anticipate and address potential issues in your design：

- Anticipate edge cases: high traffic, low memory, and high user concurrency
- Plan for failure: how to maintain availability and consistency
- Consider scalability
- Consider security: protect sensitive data and ensure security
- Be prepared to explain why you made certain design decisions and how they address edge cases and constraints.

### 0.4 Goal and Purpose

Interviewer:

- assesses a candidate's ability to combine knowledge, theory, experience, and judgment toward solving a real-world engineering problem with significant ambiguity.
- Interviewers are more interested in your thought process throughout the interview than in your final design.

Interviewee:

- The key aspect of system design is to identify the problem area and trade off, and be able to justify a decision over another.
- The success heavily depends on your ability to communicate your thought process and hold a discussion (collaborate).
- Demonstrate your thought process and domain-specific knowledge; Presentation matter.
- It is critical to demonstrate your ability to recognize and evaluate trade-offs, as it reflects your understanding of various design aspects and their implications

### 0.5 Expectations

- Mid-level System Designers
  - Be able to identify and address performance, scalability, and reliability issues
  - be well-versed in various **architectural styles, design patterns, and their trade-off**
- Senior System Designer
  - strong expertise on System Design
  - tackle some of the **most challenging** design issues
  - have the insight to address **long-term issues** that may affect a system over its lifetime
  - speak toward **bottlenecks and long-term scalability** of the system
  - feel confident enough to lead and mentor other designers in regard to **system design principles and best practices**
  - Can **review, evaluate, and evolve** a system design
- Principle/Lead System Designer
  - extensive knowledge of System Design, **its history, and industry trends**; (past, current, and future)
  - be **recognized** for designing and implementing complex and large-scale systems; (have a good reputation)
  - have a deep and thorough understanding of trade-offs, performance optimizations, and long-term scalability

### 0.6 Should do

Start with process → methodology → scale → reliability → meta-mindset.

- Process & Communication
  - Lead and drive an Open-ended conversation → Treat it like guiding juniors, discussing with peers, and presenting to seniors.
  - Regularly monitor the time on track → Keep progress balanced between breadth and depth.
  - Evaluate the solution, and engage in feedback, discussion and question → Show adaptability and collaboration.

- Design Methodology
  - Get the skeleton in the place and then start optimizing (optimization is an evolutionary process) notch by notch.
  - Do NOT over-design or under-design → Balance simplicity with completeness.
  - Everything is a trade-off; Make points with justification; Defend your design.
  - System design is similar to Object/Class Design → Why need such a component? Which APIs should it provide? Which data should it manage?
  
- Scalability & Performance
  - Identify potential bottlenecks and future problems (scale).
  - Usage patterns, and security.
  
- Reliability & Resilience
  - No single-point failure (to achieve high reliability, no data lost).
  - Describe failover and impacts on users and Service Level Agreements (SLAs).
  - Backup and disaster recovery.

- Meta-Lens (global mindset / cross-cutting principles)
  - Trade-offs → Every decision should consider pros/cons.
  - Communication → Clear explanations are always required.
  - Time-awareness → Keep an eye on progress throughout.
  - Iterative refinement → Don’t aim for perfection in one go.

- Analogy between Class Design and System Design:
  - In Object/Class Design, you clarify:
    - Why does this class exist? (responsibility)
    - Which methods/functions should it expose? (interface)
    - Which attributes should it store/manage? (state/data)
  - In System Design, you do the same but at a larger scale:
    - Why does this component/service exist? (responsibility)
    - What APIs does it expose? (interface)
    - What data does it store/manage? (state/data)

## 1 Ask clarifying and high-level design questions to **scope** the problem well

It is what an interviewer is expecting from us; the interviewer is evaluating your investigative abilities

- to gather requirements, and to **scope** the problem
- to outline use cases, to gather constraints, and to validate our assumptions
whenever you interact with a platform; think of who, why, what, and how. Looking into designing the incentives for all kinds of users for them to interact with the system.

The functional requirements are the **features and functionalities** that the user will get, whereas the non-functional requirements are the **expectations in terms of performance** from the system.

### 1.1 Functional Requirements (Product Features/Functionalities + User Requirements)

#### 1.1.1 Product Features/Functionalities

- **Goal**: What is the goal?
- **Functions**: What does the system do?
- **Input and output**: What are the inputs and outputs of the system?
- **Criticality**: What is the criticality of the system?

#### 1.1.2 User requirements

- **User types**: Who is going to use it? How many kinds of users are there? The categories of people. E.g. Creator, Viewer, and Advertiser.
- **Purpose**: Why? Their incentives to use the system. We develop the whats (incentives/procedures) and the whys (why someone would interact with that kind of content).
- **User cases**:
  - What are the use cases?
  - How are they going to use it?  
  - What kind of **operations** does the system support?
  - Read-Heavy vs Write-Heavy

### 1.2 Non-Functional Requirements (Product Properties + User Expectations in term of performance) (PACELC + Reliable + Scalability + Extensibility)

CAP theory. CP or AP? **PACELC (When Partition, Availability or Consistency, Else Latency or Consistency)**; High reliable and high scalable;  
Reliability, Redundant, Stable, Security, Availability 100 up-time?, Simplicity vs Complexity, Maintainability, Consistency, or eventual consistency 

Need enough resources to handle the increasing load; the system must be simple so that it is easy to scale at any point in time; **performance should always be increased with scalability**.

#### Availability

- System must be highly available to keep the users **engaged** with the platform
- **Every request received by a non-failing node in the system must result in a response**. Refers to the system's ability to remain accessible even if one or more nodes in the system to go down.
- Definition: **the percentage of the time that a system remains operational to perform its required function in a specific period under normal conditions**;
  - Measured in a number of 9s, three 9s - 99.9%, four 9s - 99.99%
  - **Availability = Uptime ÷ (Uptime + Downtime)**
  - **Mean Time Between Failures (MTBF)**: total uptime / # of failures. This is the **average time between failures**.
  - **Mean Time to Repair (MTTR)**: total downtime / # of failures. This is the **average time taken to recover from a failure**.
- Availability can be **achieved** through CDN (Cache), redundancy (replica of servers and data) , load balancing (distribute the requests only to the active healthy nodes by local LB and to different locations by global LB), choosing high availability databases
- V.S. Reliable: if a system is reliable, it is available. However, if it is available, it is not necessarily reliable.

#### Reliability

- **Goal**: keep delivering its service even when one or several of its software or hardware components fail; handle faults, failures, and errors;  
  - A **fault** is a defect or flaw in the system's components. A fault is a defect or flaw in the system's hardware or software that can potentially cause the system to deviate from its expected behavior.
  - A **failure** is the visible manifestation of a system not performing as expected due to one or more faults.
  - An **error** is a human action or decision that can introduce faults or lead to failures in the system.
  - fault (invisible) with/without error (human action) => failure (visible)
  - **Durability**: any uploaded data like photo or video should never be lost
- **achieve** such resilience with a cost in order to eliminate every single point of failure (vulnerable), data lost, authentication(???)
  - client:
    - use local storage, and resend after reconnect
  - System:
    - redundancy of the hardware & software components and data
    - load balancer: achieve with health check (heartbeat protocol, gossip protocol), and monitoring services with alerts
    - services are decoupled and isolated

#### Efficiency/Performance (Latency and Throughput)

- Efficiency is measured mainly by:
  - Latency / Response Time
  - Throughput / Bandwidth

- Key Metrics
  - **Response Time** = time difference between request and response.
  - **Latency** = time taken for data to travel between two points. speed of one request (delay)
  - **Throughput** = amount of work done / number of operations completed per unit time. volume of work handled per unit of time.
  - **Bandwidth** = maximum data transfer capacity of a network. physical network capacity.

- Techniques to Improve Efficiency
  - (a) Reduce Latency
    - Geographically distribute servers closer to users.
    - Use CDNs for frequently accessed documents, images, and media.
    - Add cache clusters above database clusters.
    - Use indexes for faster data lookup.
  - (b) Increase Throughput
    - Partition & shard data → parallel reads/writes across machines.
    - Use multiple machines to parallelize processing.
    - Employ distributed systems (datastores, caches, compute nodes).
  - (c) General Optimization
    - Cache at every layer: client, web server, app server, database, file system, storage.
    - Choose the right technology for the right feature.
      - Different datastores for different access patterns.
      - Different distributed caches based on use case and frequency.
    - Select the appropriate programming language/runtime for the workload.

- User Experience Angle
  - Efficiency isn’t just raw metrics — it’s about smooth experience (e.g., video streaming must feel seamless).

#### Scalability

- **Definition & Core Idea**
  - Scalability = the ability of a distributed system to **handle growth** in workload, users, and data **without degradation in performance**.
  - A system is scalable if **adding more resources** results in **proportional performance improvements**.
  - Goal: performance should increase smoothly with growth while keeping complexity manageable.

- **Types of Scaling**
  - **Vertical Scaling (Scale Up):** add more power (CPU, RAM, disk) to a single server.
  - **Horizontal Scaling (Scale Out):** add more servers/machines to distribute workload.
  - **Elastic Scaling (Scale Up & Down):** system should scale **both ways** automatically depending on traffic (auto-scaling policies).

- **Principles & Requirements**
  - System should remain **simple and easy to scale**.
  - **Performance ↔ Resources**: Ideally performance should always increase with added resources.
  - Must prevent bottlenecks in:
    - **Storage**
    - **Bandwidth**
    - **Concurrent user requests**

- **Techniques to Achieve Scalability**
  - **Caching & CDN**
    - CDN: brings content closer to users, reduces bandwidth needs.
    - Caching layers: reduce repeated work and latency.

  - **Database Strategies**
    - Read replicas: distribute read queries.
    - Sharding (horizontal partitioning): split database by user ID, range, hash, etc.
    - Separate read/write operations onto different servers.

  - **Partitioning**
    - Split large files/blobs into **smaller chunks** served by multiple servers.
    - Use **partition mapping** to track and route requests.

  - **Service Architecture**
    - Microservices: isolate different services to scale independently.
    - Load balancers: distribute traffic across servers.
    - Specialized servers: optimize general-purpose servers for specific tasks via performance tuning.

- **Key Takeaways**
  - Scalability ≠ just “adding machines” → requires **smart architecture**.
  - **Auto-scaling policies** balance cost, availability, and performance.
  - Always design to avoid **single points of failure** and **bottlenecks**.

- a distributed system can continuously evolve in order to support the growing amount of work (handle the increasing amount of user requests, and work with the more data);
- increase resources and performance with increasing load and traffic over the existing system without affecting the complexity and performance; need enough resources to handle the increasing load, for it would be increased at any point in time; should be simple and easy to scale; performance should always be increased with scalability
- The system should be able to scale up and down, depending on the number of requests; Auto-scaling policies are crucial for maintaining the desired level of performance, availability, and cost efficiency

#### Consistency

All nodes see the same data at the same time, no matter users read/write from/to any node. Equivalent to having a single up-to-date copy of the data. Consistency is the agreement between multiple nodes in a distributed system to achieve a certain value.

- **Strong consistency**: the data in all nodes is the same at any time; offers up-to-date data, but at the cost of high latency.
- **Weak consistency:** no guarantee that all nodes have the same data at any time.
- **Eventual consistency:** ensure data of each node of the database get consistent eventually; offers low latency at the risk of returning stale data.
- high consistency on messages can be achieved with the help of a FIFO messaging queue with strict ordering

#### Concurrency

To maximize system's performance: high bandwidth and high throughput.

#### Serviceability or Manageability (simplicity)

- is the **simplicity** and **speed** with which a system can be repaired or maintained.
  - The ease of diagnosing and understanding problems when they occur
  - The ease of making updates or modifications
  - how simple the system is to operate

#### Durability

- The data, once uploaded, shouldn't be lost unless users explicitly delete that data.
- The replication and monitoring services ensure the durability of the data.

#### Security

Be secure via end-to-end encryption

### 1.3 Achieve NFR (Non Functional Requirement)

The table summarizing how to achieve various important attributes in system design:

- The table content is organized in this ways:
  - Same order as the prioritized NFRs
  - In Strategies; start from theory/principle; from big scopes to small scopes; from Frontend to Backend as the request goes through

| Attribute           | Strategies to Achieve                                                                                 |
|---------------------|------------------------------------------------------------------------------------------------------|
| High Availability   | - Redundancy and failover<br>- Disaster recovery planning<br>- Geographic distribution<br>- Multi-region active-active architecture<br>- Load balancing<br>- Automated scaling<br>- *Isolation*<br>- Zero-downtime deployments<br> |
| Reliability         | - Redundancy and failover<br>- Monitoring and alerting<br>- Automated testing<br>- Backups and data replication<br>- Disaster recovery planning |
| Low Latency         | - Use of Content Delivery Networks (CDNs)<br>- Distributed caching<br>- Edge computing<br>- Efficient algorithms<br>- Optimized network architecture |
| High Throughput     | - Horizontal scaling<br>- Load balancing<br>- Use of asynchronous messaging<br>- Distributed databases<br>- Optimized data processing pipelines |
| Scalability        | - Horizontal scaling<br>- Content delivery networks (CDNs)<br>- Auto-scaling<br>- Microservices architecture<br>- Caching<br>- Asynchronous processing<br>- Distributed databases<br> |
| Consistency         | - Strong consistency models<br>- Distributed transactions<br>- ACID compliance<br>- Event sourcing<br>- Eventual consistency for specific use cases |
| Concurrency         | - Optimistic concurrency control<br> - Proper locking mechanisms<br>- Use of distributed locks<br>- Isolation of critical sections|
| Security            | - Authentication and authorization mechanisms<br>- Encryption<br>- Firewalls<br>- Intrusion detection systems<br>- Regular security audits<br>- Least privilege principle |

| Strategy                                         | Attributes Achieved                                     |
|--------------------------------------------------|---------------------------------------------------------|
| Redundancy and failover                         | High Availability, Reliability                         |
| Disaster recovery planning                     | High Availability, Reliability                         |
| Load balancing                                 | High Availability, High Throughput                     |
| Automated scaling                              | High Availability, Scalability                         |
| Isolation                                       | High Availability, Scalability                         |
| Geographic distribution                        | High Availability                                    |
| Multi-region active-active architecture        | High Availability                                   |
| Zero-downtime deployments                      | High Availability                                   |
| Automated testing                              | Reliability                                           |
| Backups and data replication                  | Reliability                                          |
| Horizontal scaling                             | Scalability, High Throughput                           |
| Microservices architecture                     | Scalability, High Throughput                           |
| Auto-scaling                                   | Scalability, High Throughput                           |
| Asynchronous processing                        | Scalability, High Throughput                         |
| Distributed databases                          | Scalability, High Throughput, Consistency             |
| Caching                                        | Scalability, Low Latency                             |
| Content delivery networks (CDNs)               | Scalability, Low Latency                             |
| Strong consistency models                      | Consistency                                          |
| Distributed transactions                       | Consistency                                          |
| ACID compliance                                | Consistency                                          |
| Event sourcing                                 | Consistency                                          |
| Eventual consistency for specific use cases    | Consistency                                          |
| Proper locking mechanisms                     | Concurrency                                          |
| Isolation of critical sections                 | Concurrency                                          |
| Use of distributed locks                       | Concurrency                                          |
| Optimistic concurrency control                 | Concurrency                                          |
| Authentication and authorization mechanisms   | Security                                             |
| Encryption                                     | Security                                             |
| Firewalls                                      | Security                                             |
| Intrusion detection systems                    | Security                                             |
| Regular security audits                        | Security                                             |
| Least privilege principle                      | Security                                             |

Remember that achieving these attributes often involves trade-offs, and **the strategies you choose will depend on your specific application requirements, budget, and the complexity you're willing to manage**.

### 1.4 Prioritize requirements

Break it down, to the most important, minimal features for your system.

### 1.5 Design Considerations (no do, or assumption)

- Security: No user authentication or authorization; both are already completed
- Result: **get all or nothing, not a partial result**
- **Fairness** and ethical
- **Prevent abuse**: put some restriction to stop system abuse
  - limit the size of text or image or video
  - add a rate limiter (prevent abuse behavior, provide a fair and reasonable use of the resource's capacity when sharing among many users, control the cost of operations and avoid excess costs)
- Assumption: **surge in traffic**

## 2 Capacity Estimation and Constraints: Traffic, Storage, Network/Bandwidth, Memory(cache) Estimation

- Goal
  - Estimate the **scale of the system** we are going to design.
  - The estimation will be helpful later when focusing on scaling, partitioning, load balancing, and caching
  - What are the constraints?
  
- Terms
  - **traffic** is the user request from users to servers; client => servers
  - **storage** is the user data or user-request data on disk; data on servers' disks
  - **bandwidth**  is traffic from servers to users; client <= servers
  - **memory** is the cache capacity in order to improve the performance, esp. for read-heavy

- **Read-heavy vs Write-heavy**
  - based on the read-heavy or write-heavy machine we can apply the 80–20 rule (or 90-10, or others)
  - If this is a **read-heavy**, estimate **read throughput**
  - If a system is **write-heavy** then we need to estimate the **Storage** requirements per day, per year, and for 5–10 years

### 2.0 The common data used in estimation (TODO from Meta system design post???)

- second per day? 86400 - > 10^5;

- A modern-day server capacity

### 2.1 Traffic in write/second, or read/second

#### **Users**

- User types, e.g. riders vs drivers, guest vs owner
- Total user
- New users added per day
- DAU (Daily active users)
- Active connections per minutes
- Meta data required for each user

#### **Requests:** How many requests per second/day do we expect?

- Type: (read, write, search); fast reads, fast writes, or both?
- Count: write and Read count in million per day
- Ratio: write : read ratio; generally 5 : 1 (or 100: 1)
- Size: the average size of an reading or writing objects

How much will it grow each year?

### 2.2 Storage in TB or GB/year

- **Write**: Write count x write size; e.g. 400M x 300B = 120GB/day

- Total files/write ???
- average file/write sizes ???; Limit on user input for each paste or a certain time (text amount, image size, user URL size) (not abuse)
- Metadata: user information, metadata about these writes

- **Total:** Total Storage Capacity including everything
  - **Others:** metadata, thumbnail, different resolutions, etc
  - **Growth:** Estimate in 5 or 10 years; Growth rate? e.g. 120GB x 365 days x 5 years = 200TB
  - **Margin:** to keep some margin, If never more than 70% or 80% of capacity; Assuming a 70% capacity model (we don't want to go above 70% of the total capacity of our storage system); 200TB / 80% = 250TB
  - **Replication:** replication for fault tolerance; e.g. 250TB * 2 = 500TB
  (500TB / 4T/server = 125 servers) (NOTE: too big for a single machine, so must be partitioned) (so is the cache)

### 2.3 Bandwidth in KB/s or MB/s

Bandwidth will decide how to manage traffic and balance load between servers. ???

- **Ingress (upload, incoming):** write count per second/minute * write average size
- **Egress (download, outgoing):** read count per second/minute * read average size
- **Ratio:** read or write intensive (need partition, or cache, or cache strategies)

### 2.4 Memory (cache) in GB or TB /day

- 80-20 rule: 20% of hot pastes generate 80% of traffic, so only cache these 20% of pastes
- 20% of daily traffic and based on client's usage patterns, can adjust how many cache servers we need
- 20% x read count / **per day** x read average size

Benefit: Low latency (real time)

### 2.5 Modern Server Capability

- Goal
  - expect to use reasonable ballpark figures to do sanity-check scale
  - Requests per second that a server can handle; used in estimating how many servers are required

#### ⚙️ Modern-Day Server (Ballpark Capacity for Estimation)

- **CPU**
  - ~32–64 vCPUs (often ~2.5 GHz each)
  - Each core can handle ~1k–10k lightweight requests/sec (depending on workload, language/runtime).
  - Rule of thumb: **1 core = 1k RPS for a typical web workload**.
- **Memory (RAM)**
  - ~128 GB is common in production servers (range: 64 GB – 512 GB).
  - Rule of thumb: **assume 100 bytes to 1 KB per object in memory** → can hold 100M–1B objects in memory if optimized.
- **Disk (Storage)**
  - SSD: ~1–4 TB per server (NVMe can be much faster).
  - Throughput: ~500 MB/s – 2 GB/s.
  - Latency: ~100 µs – 1 ms.
  - Rule of thumb: **assume 500 MB/s sequential I/O, 10k–100k IOPS**.
- **Network Bandwidth**
  - ~10–25 Gbps (cloud VMs often limited to ~10 Gbps).
  - 10 Gbps ≈ 1.25 GB/s max.
  - Rule of thumb: **a single server can push ~1 GB/s over the network**.

#### ⚡ Practical Constants for Quick Estimation

- **1 day ≈ 100k seconds** (instead of 86,400).
- **1 server ≈ 100k RPS capacity (front-end, stateless, well-optimized)**.
- **1 server ≈ 1 Gbps sustained throughput**.
- **1 server ≈ 100M–1B cached objects in memory (depending on size)**.
- **1 SSD ≈ 1–2 TB usable space, 500 MB/s read/write**.

## 3 System API design

**Goal:**

- The goal of the APIs is to make as much as clean & simple as possible to be simple to understand for everybody
- Establish the exact **contract** expected from the system and ensure if we haven't gotten any requirements wrong
- APIs can translate (map) feature set into technical

**Consideration:**

- A simple common way is making CRUDs
- Remember to use always a key for secure authentication; throttle users based on their allocated quota
- Decide if our application will be Client Driver or Server Driver
- How do we want to split our requests into different requests/APIs

**Operations:** (verbs and actions on objects)

- **CRUD**: Create/paste/post, Read/get, Update/put, Delete
- Others: Search, list, store, stream, request, like or unlike, reply, follow or unfollow, retweet or re-post? or share?
- Registration or authentication
- These operations might work on different objects/levels/scopes

**API Styles:**

- Terms
  - SOAP API (Simple Object Access Protocol)
  - REST API (Representational State Transfer)
  - GraphQL (Meta)
  - gRPC (Google Remote Procedure Call)

- Comparison

| Feature            | SOAP 🧩                    | REST 🌐                        | GraphQL 🔍                             | gRPC ⚡                                   |
| ------------------ | -------------------------- | ------------------------------ | -------------------------------------- | ---------------------------------------- |
| Type               | Protocol                   | Architectural style            | Query language/runtime                 | RPC framework                            |
| Data format        | XML only                   | JSON, XML, etc.                | JSON                                   | Protobuf (binary)                        |
| Transport          | HTTP, SMTP, TCP            | HTTP only                      | HTTP (POST)                            | HTTP/2                                   |
| Contract/schema    | WSDL                       | OpenAPI/Swagger                | GraphQL schema                         | .proto files                             |
| Stateless/stateful | Often stateful             | Stateless                      | Stateless                              | Stateless (with streaming)               |
| Query flexibility  | Fixed operations           | Endpoint-based                 | Client chooses fields                  | Fixed RPC methods                        |
| Performance        | Heavy (XML)                | Good (JSON, caching)           | Moderate (parsing overhead)            | Excellent (binary, multiplexed)          |
| Use cases          | Banking, legacy enterprise | Public web APIs, microservices | Frontend/mobile APIs, flexible queries | Microservices, internal comms, real-time |

- Summary
  - SOAP = enterprise, strict, legacy-heavy.
  - REST = simple, web-friendly, most common.
  - GraphQL = flexible, client-driven, great for UIs.
  - gRPC = high-performance, streaming, great for service-to-service.

- Quick Decision Flow (Interview-Friendly)
  - Is this an enterprise system with strict contracts/security? → SOAP
  - Is this a public web/mobile API, simple CRUD, broad developer base? → REST
  - Do clients need flexible queries, avoid over-fetching, multiple frontends? → GraphQL
  - Is this microservices, high-performance, real-time streaming? → gRPC

**Parameters:**

- user_id: uniquely specified the user performing the action;  throttle users based on their allocated quota
- All kinds of information about the file/video/picture/like/dislike/comments/etc, like name/title, user/place ID, category/type, description, latitude, longitude, rating, hashtags, channel, language, privacy (private or public)
- Search Query: category/type(videos, images, comments), keywords, user_location, radius, name_of_place
- maximum Results to Return
- sort(number) Optional sort mode: 0 - latest first, 1 - best matched, 2 - most liked
- page_token(string) specify a page in the result set that should be returned
- Timestamp

**Return:**

- (JSON or XML) a list of results matching the search query
e.g. This process returns a JSON object that contains a list of all the possible items in the specified category that also fall within the specified radius
- Each entry has a place name, address, category, rating, and thumbnail

## 4 Database Design (Define Data Model and Choose Database)

### 4.0 Data Model

**Benefit:** Defining the data model in the early part of the interview will

- Identify various **entities** of the system, and how they will **interact** with each other
- Clarify how data will **flow** between different system components
- Determine which database storage schema is required and which database type is preferred
- Guide for data partitioning and management
  
**Static and Dynamic to identify:**

- Identify various system **entities** (primary objects)
- their **relationship** (static)
- how they will **interact** with each other (dynamic, create, extract, transform, load, etc.)
- how these objects **flow** between different system components

**Consideration:**

- Which database system should we use? NoSQL like Cassandra or MySQL?
- Separate the most frequently and less frequently accessed storage clusters from each other for optimal access time; then can apply different configurations, cache strategies, shardings, etc.
- Separate the read and the write onto different database; CQRS (Command Query Responsibility Segregation) separates the responsibility of reading data (queries) from writing/updating data (commands) in a system；

### 4.1 Database Schema or components/classes and their relationship/connection (static)

- emphasizes **scale + trade-offs** — which is exactly what interviewers want.
- Entities + Relations → Metadata vs Objects → Indexing → Scaling (Sharding/Replication/Caching) → Trade-offs.

- Core Idea
  - **Schema = Entities + Relationships** (static view of the system).
  - Define:
    - **What are the core objects?** Entities: (User, Item, Place, Review, Photo…)
    - **How they connect?** Relationships (via primary/foreign keys)s: 1–1, 1–many, many–many → use PKs & FKs.

- Design Considerations
  - **Data volume**: millions vs billions of records?
  - **Data size**: Small (<1KB) vs large (MBs, needs object storage).
  - **Relationships**: Many-to-one (users → items), one-to-one (user → profile), many-to-many (users ↔ places via reviews).
  - Access patterns: Reads vs Writes? Search vs Scan?

- Storage Strategy
  - **Metadata storage**: relational DB (MySQL/Postgres) or distributed KV (Cassandra/DynamoDB).
  - **Object storage**: large files (images, videos, blobs) → S3, GCS, HDFS.
  - Separate metadata (fast queries) from object storage (scalable, cheap) for scalability and cost efficiency.

- Example Entities
  - **User**: `UserID (PK), Name, Email, CreationDate, LastLogin, Birthday`.
  - **Item**: `ItemID (PK), Description, Type, UserID (FK), Path, LikesCount`.
  - **Place**: `PlaceID (PK), Name, Category, Lat/Long, Rating`.
  - **Review**: `ReviewID (PK), PlaceID (FK), UserID (FK), Description, Rating`.
  - **Photo**: `PhotoID (PK), UserID (FK), PlaceID (FK), Path, CreationDate`.

- Indexing & Query Optimization (make it faster to search through the table and find the row or rows that we want)
  - **Indexes speed up reads** but slow down writes.
  - Choose indexes based on **query patterns** (how users will access the data) (e.g., search by `UserID`, sort by `CreationDate`, filter).
  - Trade-offs: performance (query/read speed) vs storage (cost) vs write speed (latency).

- Scalability Considerations
  - **Sharding / Partitioning**: split large tables (e.g., user Id, users by region/geography, items by ID range).
  - **Partitioning**: Divide tables/files for parallel access.
  - **Replication**: read replicas for scaling reads. Master for writes, replicas for reads.
  - **Caching**: frequently accessed metadata in Redis/Memcached. CDN for media.
  - **Avoid bottlenecks**: distribute load across storage + DB layers.

- Interview Best Practices
  - Start with **entities + relationships**.
  - Then explain **storage choices** (metadata vs object storage).
  - Highlight **scaling strategies** (sharding, replication, caching).
  - Discuss **trade-offs** (RDBMS vs NoSQL, index impact, storage cost).
  - Keep details **high-level first**; dive deep only if interviewer asks.

Common Entities (e.g.)
- User: id (primary key, int), name (varchar 20), email (varchar 32), CreationDate (datetime, 4 byte?), LastLogin (datetime), Birthday (datetime)
- Description (512 or 256), phone (12), path(256, path to the object storage)
- Item/Object (picture, video, comment, etc): CreationData, ExpirationDate, type (int), Description (varchar 512), Category: (smallint), UserId(int, creator), contents(varchar 256), Path(varchar 256), likes_count, view_count
- Location: latitude, longitude (int - 4 bytes, or 8 bytes)
- Numbers: num of likes/dislikes (int), num of comments, num of shares, num of views
- Rating (how many stars a place gets out of ten)
- Photo: PhotoID(int, 8 bytes, 64 bits), UserID(int), Photo_Path(varchar 256), Photo Latitude & Longitude (int), User Latitude & Longitude (int), CreationDate(datetime), or Place_ID (8 bytes, foreign key)
- Place: ID (8 bytes, 64 bits), Name(256 bytes), Description(1,000 bytes), Category (8 bytes ???), Latitude (8 bytes), Longitude (8 bytes), Phone(the foreign key, 8 bytes), Rating, address, business hours, menu
- Review: ID (8 bytes), Place_ID, User_ID, Description (512 bytes), Rating (1-5, 1 byte)

latest (CreationDate), popular (likes, comments, shares), relevant (used in ranking)   <br>

Indexing needs a primary key on the table with a unique value; Using one or more columns <br>
Ordered indexing (increasing or decreasing) or Hash-indexing <br>

### 4.2 Choose Database

Choosing the proper database is a **critical decision** that significantly impacts **performance, scalability, reliability, and cost** of the system.
**Structured for recall (Factors → Options → Hybrid).**

#### Key Factors to Consider

- **Data Model**
  - Structured: Relational (SQL).
  - Semi-structured: Document stores (JSON-like).
  - Unstructured: Key-value, object storage.
  - Specialized: Graph, time-series, columnar.

- **Data Size & Volume** (to handle the scale of data efficiently)
  - Expected growth rate and storage needs (GB → PB).
  - Small objects vs. large blobs.

- **Query & Access Patterns**
  - Read-heavy, write-heavy, or mixed workload.
  - Need for joins, aggregations, or full-text search: Assess the frequency and complexity of joins and aggregations required in the queries and choose a database that can handle them efficiently.

- **Performance Requirements**
  - Latency (response time), throughput (requests/sec).
  - Indexing, caching, and replication support.

- **Consistency & Transactions**
  - Strong consistency (ACID) vs. eventual consistency (BASE).
  - Transactional guarantees (banking vs. social feeds).

- **Scalability**
  - Horizontal scaling: sharding, partitioning, replication.
  - Vertical scaling: bigger machines.
  - Auto-scaling for elasticity.

- **Data Integrity & Constraints**
  - Need for unique keys, foreign keys, normalization.
  - Trade-off: normalization (less redundancy) vs. denormalization (faster reads).

- **Reliability & Availability** (ensure data durability and system resilienc)
  - Replication, failover, high availability.
  - Backup & disaster recovery features to ensure data safety.

- **Cost & Ecosystem**
  - Licensing & cloud service costs.
  - Integration with existing tools, frameworks, monitoring.

#### Database Options

- **Relational Databases (SQL)**
  - MySQL, PostgreSQL, Oracle.
  - Good for structured data, joins, transactions.
  - Limited horizontal scalability.

- **NoSQL Databases**
  - Key-Value (Redis, DynamoDB): ultra-fast lookups.
  - Document (MongoDB, Couchbase): flexible schema.
  - Columnar (Cassandra, HBase): time-series, analytics.
  - Graph (Neo4j): relationships (social networks, fraud).

- **Object Storage**
  - Amazon S3, HDFS.
  - Best for large blobs (images, videos, logs).
  - Metadata stored separately (SQL/NoSQL).

#### Hybrid Approach (Polyglot Persistence)

Most real-world systems combine multiple storage types:

- SQL DB → metadata (users, accounts).
- NoSQL → fast access, high-scale workloads.
- Object Storage → large files.
- Cache/CDN → latency reduction.

## 5 High-Level Design — This is pretty much a template, you can put in front of interviewers

- **Goal**
  - The candidate should identify various **system entities**, how they will **interact** with each other, and how data would be **flowing** in the system
  - **Static Structure**: components, their relationship (e.g. 1:1 or 1:n) and connections
  - **Dynamic Behavior**: workflow, how these components interact with each other, **event/time sequences**
  
- **Steps**
  - **Outline core components and connections (Static)**
    - Draw a block diagram with **5-6 core components/entities** of the system, which are enough to solve the actual problem from end to end.
    - Map **features → modules**
    - Define micro-services based on features/APIs (e.g. which micro-service should handle request and reply with a response)
    - Sketch the **main components + connections**
    - **Justify each design choice**
  - **Describe Request Workflow (Dynamic)**
    - Walk through what happens **from client request → backend processing → response**.
    - Explain **how data flows across components**.
    - Highlight interactions (**synchronous vs asynchronous**).
  - **Defend Trade-offs**
    - Why these components?
    - Why this communication style (REST, gRPC, message queue)?
    - **Where are bottlenecks mitigated?**

- **Common Components (Static View)**: A typical scalable and reliable system often includes:

  1. **Client** (web/mobile app, API consumer)
  2. **Load Balancer** (distributes traffic, prevents overload)
  3. **Web Tier**
     - Web server / reverse proxy (e.g., Nginx, Envoy).
     - WebSockets for real-time systems.
     - API Gateway if multiple services.
  4. **Application/Service Layer**
     - Microservices (feature-based, API-based).
     - Service partitioning for scaling.
  5. **Cache Layer**
     - Redis, Memcached, CDN.
     - Used at multiple levels (client-side, service-side, DB-side).
  6. **Database Layer**
     - SQL/NoSQL depending on use case.
     - Master-slave or leader-follower clusters.
     - Sharding, replication, partitioning for scale.

- **Supporting Components (Optional but Good to Mention)**

  1. **VPCs & Networking**
     - Public vs private subnets.
     - API gateway in public, DB in private.
  2. **Rate Limiter**
     - Protects from abuse (DDoS, API overuse).
  3. **Admin / Manager Node**
     - Access privileges, dashboards, console.
  4. **Monitoring & Logging Services**
     - Metrics (Prometheus, Grafana) (The System’s Health Report). Metrics are time-series data points that allow you to quantify the performance and health of every component. They are crucial for setting up Alerts.
     - Alerts, logs (ELK stack, Datadog).
  5. **Backup & Disaster Recovery**
     - Snapshots, multi-region replication.

- Notes
  - Application layer = **brains** → handles all incoming & outgoing requests.
  - Use **Single Responsibility Principle**: small, autonomous services that scale and configure independently.
  - In interview: **start simple**, then **iterate with scaling, caching, failover** when asked.

## 6 Low-Level Design (LLD) - Deep Dive into Core Components (Detailed Component Design)

- **Purpose**
  - Go deeper into the **design of 2–3 critical components** (**performance-sensitive** or **core to functionality**) with the guidance of the proper [LLD Deep Dive Lenses](#60-lld-deep-dive-lenses-short-checklists-for-common-components-to-deep-dive).
  - Show understanding of **how data flows and how requests are handled at a detailed level**.
  - Demonstrate ability to **evaluate trade-offs, handle failures, and optimize performance**.

- **Approach**
  
  1. **Component Selection**: (guided by lens)
     - Either pick components yourself or ask interviewers for guidance. The interviewers' feedback should always guide us to what specific parts need focus, elaborate on, and further discussion.
     - **Prioritize** components that are **core to performance, reliability, or correctness**.

  2. **Detail the Component Design**
     - **Goal**: Explain what each component does, how it works internally, and how it interacts with others.
     - External View → Internal Structure → Dynamic Flow → Justifications; a natural top-down flow — from how others see the component to how it behaves internally.
     - **External View – Responsibilities and Interfaces (Context First)**
       - Start from what the component promises to do and how others interact with it
       - What is the responsibility or role of this component?
       - What are its inputs and outputs?
       - What APIs or interfaces does it expose?
       - **Purpose**: Give interviewer the big picture context before diving into internals.
     - **Interaction View – Communication and Workflow (Dynamic Behavior)**
       - Describe how it interacts with other components during typical operations.
       - Read Flow + Write Flow
       - This is the “dynamic view” — runtime behavior across components.
     - **Design Justifications and Trade-offs**
       - Finally, highlight reasoning to show maturity of thought.
       - Why this data structure or algorithm?
       - What trade-offs exist?
     - **Static Structure (what it is)**: Describe how the component works internally (data structures, algorithms, APIs) (Static as class definition: internal state, functionality, and external APIs).
     - **Dynamic behavior (how it works)**:
       - Explain how it **interacts** with other components (Dynamic behavior).
       - Walk through **read and write flows** with examples.

  3. **Design Alternatives**
     - Present **2–3 possible approaches**, list **pros and cons**, and justify your choice.
     - Always tie back to **system constraints (scale, latency, cost, complexity)** which are principles to choose and justify the approaches. Consider and Discuss potential solutions and trade-offs between different options while keeping system constrains in mind

  4. **Failure Handling**
     - What happens if a request fails? (e.g., duplicate key, timeout, partial write).
     - How are retries, error handling, and fault tolerance designed?

  5. **Performance Optimizations**: Reduce **latency** using (Read, Write, Data Processing Lens):
       - **Caching**: Read (client, app, DB, CDN).
       - **Prefetching / Pre-calculation**: Data Processing (e.g., pre-computing heavy queries). Customer behavior can be predicted, and heavy customer requests can be pre-calculated and saved using customer proxy pre-cache.
       - **Parallelization / Asynchronous processing**: Write (async queues, background jobs)
       - Example: Predict customer behavior and pre-cache heavy queries via a proxy.

- **Low-Level Design (Component Deep Dive Template) - Diagram + Deep Dive Lenses** to have both a **visual map** and a **checklist** for interviews.

``` arduino
+------------------------+
| Client Request (R/W)   |
+------------------------+
            |
            v
+------------------------+
| API / Service Layer    | <-- API Lens
| - Validation, routing  |
+------------------------+
            |
     -------------------
     | read-heavy      | write/async 
     v                 v
+----------------+   +------------------+
| Cache          |   | Queue / Async    |
| (Hot Data)     |   | (Heavy jobs)     |
| <-- Cache Lens |   | <-- Queue Lens   |
+----------------+   +------------------+
        |                   |
        v                   v
+---------------------------+
| Core Component (Deep Dive)|
| e.g., Feed Gen, Search    |
| <-- Data Processing Lens  |
+---------------------------+
            |
            v
+------------------------+
| Database / Storage     | <-- Database Lens
| - Partition, Replica   |
+------------------------+
            |
            v
+------------------------+
| Response / Error       |
+------------------------+
```

- **How to Use This in Interview**
  1. **Start with the flow**: “Here’s how a request flows through validation, cache, main component logic, DB, and back.”
  2. **Deep dive into one block**: For example, the **Core Component** (indexing engine, messaging queue, feed ranking, etc.).
  3. **Show trade-offs**: Talk about caching vs. DB lookup for Read, sync vs. async for Write, partitioning vs. replication for Database.
  4. **Discuss failure handling**: e.g., cache miss, DB write failure, duplicate keys.

- **How to Use in Interview**
  1. **Draw the base skeleton** above (5–6 blocks).
  2. Label each block with a **lens** (Cache Lens, DB Lens, Queue Lens, etc.).
  3. When interviewer says “deep dive here,” **zoom in using the right lens checklist**.

- **Example Walkthrough**
*Interview prompt*: *“How does your system handle hot reads at scale?”*
  - Point to the **Cache block** in diagram.
  - Switch to **Cache Lens checklist**:
    - Eviction policy? (LRU vs TTL)
    - Write strategy? (write-through vs write-back)
    - Consistency trade-off? (stale data vs DB load)
  - Conclude with justification: *“I’d use write-through cache with TTL + LRU eviction, since freshness matters but occasional stale reads are tolerable.”*

- **branching points** are mainly about *read vs write flows* for **Cache** and **Queue/Async**

  - Rule of thumb for interviews: **Reads go cache-first; Writes go DB-first (with cache updated accordingly).**
  - **Reads** (most common):

    ``` arduino
    Client → API Gateway → Cache
                  |
                  +-- [HIT] → return cached value
                  +-- [MISS] → go to DB → update cache → return
    ```

  - **Writes** (update/create/delete): (Structure: Cache + DB)
    - **Write-through**: write to DB *and* cache (synchronous, consistent). (through both Cache and DB)
    - **Write-back**: write only to cache → flush to DB later (faster, but risky if cache crashes). (Write to Cache and back, later to flush to DB)
    - **Write-around**: write directly to DB, cache updated on next read. (Write around Cache and directly to DB; later read to update Cache)

- **Queue / Async Branching**

  - **Synchronous Path (user-facing):**

    ``` arduino
    Client → API Gateway → Core Service → DB → Response
    ```

  - **Asynchronous Path (background tasks):**

    ``` arduino
    Client → API Gateway → Core Service
                            |
                            +--> Queue → Worker(s) → DB / External Service
    ```

- Rule of thumb: **If user doesn’t need the result immediately, branch into Queue.**
- Examples:
  - Email/SMS notification → push to queue, worker sends later.
  - ML model scoring → async, return immediately, update later.
  - Image/video processing → async workers.

- **Combined Flow Example**

  ``` arduino
          ┌─────────── Cache (read-heavy)
  Client ─► API Gateway ─┐
          │             │
          │             v
          │         Core Service ──► DB
          │             │
          │             └─► Queue (async tasks)
          │                   │
          │                   v
          │                 Worker(s) → DB / External API
  ```

  - Reads → Cache-first, DB fallback.
  - Writes → DB-first (update cache after).
  - Async tasks → Queue branch → processed by workers

- So in interview diagrams:
  - Draw **Cache** branch on **read-heavy path** (with arrows for read/write strategies).
  - Draw **Queue** branch on **write/async path** (**non-blocking**, background).

### 6.0 LLD Deep Dive Lenses: short checklists for common components to deep dive

- **API / Service Lens**
  - **API style**: REST, gRPC, GraphQL
  - **Granularity**: Single responsibility (SRP) vs. coarse-grained APIs
  - **Rate limiting**: How to protect downstream services?
  - **Idempotency**: Safe retries for write requests
  - **Versioning**: Backward compatibility
  - **Trade-offs**: Simple APIs vs. chatty APIs; REST vs. RPC overhead

- **Cache Lens**
  - **Where to cache?** (different component/layer: client, CDN, app server, DB, object storage)
  - **Eviction policy?** (LRU, LFU, TTL-based)
  - **Consistency?**
    - Write-through / Write-around / Write-back
    - How to handle cache invalidation?
  - **Failure handling**:
    - Cache miss → fallback to DB
    - Cache server failure → retry, degrade gracefully
  - **Trade-offs**: Faster reads vs. stale data / higher memory cost

- **Queue / Async Processing Lens**
  - **When to use?** Heavy writes, async jobs, decoupling producers/consumers (why???)
  - **Guarantees?** At-least-once vs. at-most-once vs. exactly-once delivery
  - **Ordering?** FIFO, priority queues, partitioned streams
  - **Failure handling**:
    - Retry strategy (exponential backoff, DLQ – Dead Letter Queue)
  - **Scaling**: Consumers can scale horizontally
  - **Trade-offs**: Reliability vs. latency

- **Data Processing Lens** (e.g., Search, Feed Ranking, Analytics)
  - **Pre-compute vs. On-demand**: Which parts are cached, which computed live?
  - **Batch vs. Stream**: Hadoop/Spark vs. Kafka/Flink
  - **Indexing**: Inverted index, B+ tree, bitmap index
  - **Ranking / Aggregation**: Sorting, scoring functions, ML models
  - **Failure handling**: Partial results, retries, degradation
  - **Trade-offs**: Freshness vs. latency vs. cost
  
- **Database Lens**
  - **Model choice?** Relational, key-value, document, graph, time-series
  - **Partitioning**: Sharding strategy (hash, range, geo-based)
  - **Replication**: Sync vs. async, leader-follower vs. leaderless
  - **Indexing**: Which fields to index? Trade-offs between query speed and write speed
  - **Transactions**: ACID vs. BASE, consistency model (strong vs. eventual)
  - **Failure handling**: Conflict resolution, failover strategy
  - **Trade-offs**: Consistency vs. availability (CAP theorem)

- **Security & Reliability Lens**
  - **Authentication & Authorization**: OAuth, JWT, API keys
  - **Rate limiting & throttling**
  - **Encryption**: Data at rest vs. data in transit
  - **Monitoring & Alerting**: Metrics, logs, tracing
  - **Disaster recovery**: Backups, failover plan
  - **Trade-offs**: Security vs. performance; cost vs. redundancy

- Note
  - With these **lenses**, you can quickly zoom into whatever component the interviewer asks you to deep dive.
  - For example:
    - If asked “How would you design the feed generator?” → use **Data Processing Lens**.
    - If asked “How would you handle caching for hot data?” → use **Cache Lens**

### 6.1 Scale the design

Scaling ensures the system can handle increased **traffic, data, and complexity** while maintaining **performance, reliability, and availability**.

#### 6.1.1 Purpose

Identify, address, and mitigate single points of failure (SPOFs) and bottlenecks using principles of scalable system design.

- Order of priority in interviews:
  - First eliminate **SPOFs** (ensure availability and fault tolerance).
  - Then address **bottlenecks** (improve performance and scalability).

- **Identify bottlenecks and single points of failure (SPOF).**
  - Example: database master, single cache node, central message broker.
  - Mitigation: standby replicas, failover, partitioning, distributed clusters.
- **Mitigate bottlenecks with scalable design principles, given the constraints.**
  - Always consider **trade-offs**: consistency vs availability, latency vs cost, complexity vs simplicity.

#### 6.1.2 Approaches / Methods

- **Single Point of Failure (SPOF)**
  - Ask (How to identify): “If this component fails, does the whole system fail?”
  - Fix: standby replicas, active-active load balancers, DB replication.
  - Example: don’t rely on a single database, a single LB, or a single region.

- **Bottlenecks**
  - Ask: “Which component slows down or limits throughput as traffic grows?”
  - Fix: scale horizontally, cache, shard, async queues.
  - Example: DB hot spots, overloaded app servers, large fan-out queries.

- Load Balancing: Distribute traffic across servers. Avoid dynamic hot spots and static overloaded nodes.
  - **Why**: Prevents dynamic overheating (spikes) or static overloading (long-term imbalance).
  - **What to balance**:
    - App servers.
    - Databases (read replicas).
    - Caches and queues.
  - **How**: Use L4/L7 load balancers (e.g., Nginx, Envoy, ELB) with health checks and failover.

- Caching
  - **Where**:
    - **Client-side** (store metadata locally, UI assets).
    - **Server-side** cache objects at appropriate layers (service-level, DB-level) (distributed caches like Redis, Memcached).
    - **Edge** (CDN for static content).
  - **What**: Different objects for different services (user profile, hot content, search results).
  - **Benefits**: Reduce latency, offload DB/backend, improve throughput.
  - **Challenges**: Cache invalidation, stale data, write policies (write-through, write-back, write-around).

- Partitioning (Sharding): Split data across multiple databases or storage nodes. Prevent uneven load distribution and hot partitions.
  - **Why**: Horizontally scale data storage and processing.
  - **How**:
    - Range-based, hash-based, or directory-based partitioning.
    - Split large tables/files into multiple shards.
  - **Considerations**:
    - Avoid uneven distribution (overload).
    - Prevent hotspots (popular users/content all on one shard, overheated).
    - Handle abusive users (rate limit per shard).
    - Requires careful shard key design.
  - **Tools**: Partition mapping service or consistent hashing.

- Replication: Replicate data across servers/regions for high availability.
  - **Why**: Improve availability and read scalability.
  - **How**: Master–slave (leader–follower) replication, multi-leader, or quorum-based replication.
  - **Challenges**: Consistency (eventual vs strong), replication lag, failover complexity.
  - **Use cases**:
    - Reads go to replicas.
    - Writes go to leader

- Database Indexing
  - **Why**: Speed up search and list operations.
  - **How**:
    - Build indexes on frequently queried fields.
    - Use composite indexes for multi-column queries.
  - **Trade-offs**: Balance write overhead vs read efficiency.
    - Pro: Faster reads.
    - Con: Slower writes (inserts/updates/deletes)

#### 6.1.3 Interview Strategy

When asked *“How would you scale this system?”*:

1. Check for **single points of failure**.
2. List **bottlenecks** (DB, cache, app servers, queues, storage, bandwidth).
3. Propose **incremental fixes** (LB → cache → replication → partitioning → async workers).
4. Discuss **trade-offs** at each step.

### 6.2 Partition and Replication

- Why we need them
  - Core of a distributed system, used to **scale out** and **increase availability**
  - Partitioning and replication mitigate **single points of failure (SPOFs)** and **performance bottlenecks** in large-scale systems.

- Handling Single Points of Failure
  - **Backups**: periodic snapshots + logs for recovery.
  - **Failover (fault tolerance)**: active-passive or active-active replicas to ensure continuity if one node fails.

- Handling Bottlenecks
  - **Partitioning (Sharding)**: splits data into smaller chunks across nodes → reduces overload and hotspots.
  - **Replication**: duplicates data across nodes → enables parallel reads and improves availability.

- New Challenge: Consistency; Replication introduces **consistency problems** (CAP theorem).
  - **Strong consistency**: guaranteed correctness, but slower.
  - **Eventual consistency**: higher availability and speed, but temporary data divergence possible.

- **Partition vs. Replication**

| Aspect                 | **Partitioning (Sharding)**                                                             | **Replication**                                                                 |
| ---------------------- | --------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------- |
| **Definition**         | **Splits** data into subsets (shards) across multiple servers                           | **Copies** the same data across multiple servers                                    |
| **Goal**               | Scale **write & storage** load (distribute data evenly)                                 | Scale **read throughput** and provide high availability                         |
| **SPOF Mitigation**    | Not directly (if one shard fails, only part of data is lost)                            | Yes – if one replica fails, others can still serve traffic                      |
| **Performance**        | Reduces bottlenecks by spreading load                                                   | Improves read latency and load balancing                                        |
| **Consistency Impact** | Each shard is independent, no sync needed across shards (but adds complexity for joins) | Requires syncing data → introduces consistency challenges (eventual vs strong)  |
| **Use Cases**          | Very large datasets, high write throughput (e.g., user data sharding by ID)             | Read-heavy workloads, high availability (e.g., product catalog, caching layers) |

#### 6.2.1 Replication

Organize into **sections** (definition → benefits → replication factor → replication types → replication models → trade-offs).

- **Definition**
  - Replication is the process of **duplicating critical data, components, or functions** of a system across multiple servers (often geographically distributed).

  - **Goals**: Availability -> Scalability (distribute traffic) -> Performance; Availability -> Fault tolerance
    - **Availability**: continue serving requests if one node fails.
    - **Scalability**: distribute read traffic across replicas.
    - **Performance**: reduce latency by keeping data closer to users.
    - **Fault tolerance**: tolerate server, data center, or regional failures.

  - Replication and partitioning often work together:
    - **Partitioning** distributes *different* data across nodes.
    - **Replication** maintains *multiple copies* of the *same* data.

  - **Benefits**: Goals->Benefits (Availability -> Scalability (distribute traffic) -> Performance; Availability -> Fault tolerance)
    - Removes **single points of failure** → backup/failover in case of crashes.
    - Enables **load balancing** for read-heavy workloads.
    - Reduces **latency** by keeping data geographically close to users.
    - Increases **read throughput** (read replicas).
    - Improves **durability and reliability** by storing multiple copies.

- **Replication Factor**
  - Defines how many copies of data are stored.
  - **Common setup: 3 replicas** (example):
    1. Local copy (protects against server or disk failure).
    2. Copy in another data center within the same region (protects against rack/DC outage).
    3. Copy in a different region (protects against regional disaster).

- **Replication Types (Dimension #1: Timing)**
  - **Synchronous Replication**
    - Write acknowledged only after all replicas confirm.
    - ✅ Guarantees consistency (all replicas up to date).
    - ❌ Higher latency, risk of blocking if replicas fail.
    - Commonly used *within a cluster*.

  - **Asynchronous Replication**
    - Write acknowledged after primary updates itself.
    - ✅ Low latency, primary keeps working even if replicas fail.
    - ❌ Risk of data loss if primary crashes before syncing.
    - Commonly used *across regions*.

- **Replication Models (Dimension #2: Leadership)**
  1. **Single Leader (Primary-Secondary / Master-Slave)**
     - All writes go to primary, then replicated to secondaries.
     - ✅ Simple, great for read-heavy workloads.
     - ❌ Primary = bottleneck & single point of failure. Bad for write-heavy workloads.

  2. **Multi-Leader (Multi-Master)**
     - Multiple leaders accept writes, replicate to each other.
     - ✅ Better for geographically distributed writes.
     - ❌ Conflict resolution needed (e.g., last-write-wins, custom merge logic). conflict when concurrent writes on the same data on the leaders.

  3. **Leaderless (Peer-to-Peer)**
     - Any node can accept reads/writes; replication managed with **quorums**.
     - ✅ High availability, flexible, good for write-heavy workloads.
     - ❌ More complex to configure, consistency harder to manage.

- **Trade-offs**: Replication introduces **consistency challenges**:
  - **Strong Consistency**: ensures correctness, but higher latency.
  - **Eventual Consistency**: better availability, but temporary data divergence.
  - **CAP Theorem**: systems must balance *Consistency, Availability, and Partition tolerance*.

- This structure is **clean, hierarchical, and interview-friendly**. You can now:
  1. Start with the definition & motivation.
  2. Walk through replication factor → types → models.
  3. Conclude with trade-offs (CAP).

---

- Replication — Condensed (Interview Quick Recall)

- **What it is**
Replication = keeping multiple copies of data across servers (often in different regions) to improve **availability, scalability, performance, and fault tolerance**.

- **Why**: availability, scalability, performance, and fault toleranc
  - Removes **single points of failure**.
  - Improves **read throughput** (read replicas).
  - Reduces **latency** (data closer to users).
  - Increases **durability/reliability**.

- **Replication Factor**
  - Usually **3 copies**: local, regional, cross-region.

- **Types (Timing)**
  - **Synchronous**: safe but slower (wait for all replicas).
  - **Asynchronous**: fast but may lose data if primary fails.

- **Models (Leadership)**
  - **Single Leader**: simple, read-heavy, but primary = bottleneck.
  - **Multi-Leader**: multiple writable leaders, conflicts possible.
  - **Leaderless (Peer-to-Peer)**: any node can write, needs quorums.

- **Trade-off**
  - Consistency vs Availability (CAP theorem).
  - Choose depending on workload (read vs write heavy, geo needs).

#### 6.2.2 Partition

Perfect — thanks for sharing your draft. I’ll **correct, refine, and reorganize** your note on Partition so it’s interview-ready, clear, and concise:

- Note Logic
  - what → why → benefits → how → notes
  - Definition → Benefits → Limitations → Extra notes

- **Definition**
  - Partitioning = splitting a large database or table into **smaller, more manageable parts**, and **distributing** them across multiple servers.
    - Each partition stores only a **subset of the data**, reducing the load per server.
    - Two main approaches: **Horizontal** (rows) and **Vertical** (columns).

- **Goals / Benefits**
  - **Scalability**: scale out and supports growth by distributing data across multiple servers.
  - **Performance**: queries scan less data → lower latency.
  - **Availability & Fault Tolerance**: failure in one partition does not impact others. No affect access to other partitions. 
  - **Manageability**: smaller, simpler datasets are easier to back up, restore, and maintain.
  - **Load Balancing**: spreads workload more evenly across servers for higher efficiency and lower latency.

- **Key Idea**
  - Partitioning enables **parallelism** — multiple servers can serve requests **simultaneously**.
  - Works best when partition boundaries are **well chosen** (to avoid hotspots and skew).

- **Limitations / Trade-offs**: low (Server and Database) to high (applications and queries, close to clients)
  - **Data distribution**: Uneven partitioning (hot spots) can cause performance bottlenecks.
  - **Rebalancing overhead**: Adding/removing servers requires redistributing data.
  - **Application logic**: Sometimes apps must be aware of the partitioning strategy.
  - **Complex queries**: Joins or aggregations across partitions are slower and more complex.
  - **Consistency**: Maintaining global constraints (e.g., unique keys) is harder across partitions.

- **Note**
  - Partitioning is often combined with **Replication**:
    - *partitioning* = splitting data into disjoint subsets for scale. To scale out.
    - *Replication* = multiple copies of the same data for reliability. For fault tolerance and high availability.
    - Together, they balance **scale** and **fault tolerance**.
  - Partitioning relational data typically means breaking tables **horizontally (by rows)** or **vertically (by columns)**.

##### 6.2.2.1 Horizontal Partitioning (Sharding)

- Note structure: Definition → Benefits → Methods → Criteria → Rebalancing → Limitations/Trade-offs

- **Definition**
  - Horizontal partitioning (also called **sharding**) splits a table by rows and distributes them across multiple tables or databases. Each shard contains a subset of the rows, but all shards share the same schema.
  - It is a form of **scaling horizontally (scaling out)**: adding more database instances to share the load.
  - By contrast, **scaling vertically (scaling up)** means adding more CPU, memory, or disk to a single instance.

- **Benefits**
  - Reduces read and write traffic per server.
  - Improves cache hit rate (since each shard holds less data).
  - Allows parallel writes, increasing overall throughput.
  - Smaller indexes per shard → faster queries.
  - Supports scaling out with cheaper commodity hardware.

- **Methods**
  1. **Key-based (Hash) Partitioning**
     - Hash a key attribute → assign row to a partition.
     - ✅ Pros: Even/random distribution, minimizes hot spots, easier to rebalance with *consistent hashing* after adding or removing nodes, supports heterogeneous clusters.
     - ❌ Cons: Queries spanning multiple shards require aggregation (scatter-gather).

  2. **Range-based Partitioning**
     - Rows are assigned to partitions based on a key range (e.g., `user_id 1–1000 → shard A`).
     - ✅ Pros: Simple, predictable, good locality for range queries.
     - ❌ Cons: Risk of unbalanced load (hot ranges), requires manual rebalance.

  3. **Directory-based Partitioning**
     - A lookup table/directory stores the mapping of keys → shards.
     - ✅ Pros: Flexible, partitioning logic can change without affecting applications.
     - ❌ Cons: Directory is a **single point of failure** and extra indirection adds latency.

  4. **Composite / Hybrid Partitioning**
     - Combines multiple strategies (e.g., range + hash, partition + sub-partition).
     - Useful when one scheme alone cannot balance load effectively.

- **Partitioning Criteria**
  - **Hash partitioning**: hash(key) → partition.
  - **Range partitioning**: rows fall into defined ranges.
  - **List partitioning**: explicit sets of key values per partition.
  - **Round-robin partitioning**: rows distributed cyclically.
  - **Composite partitioning**: mix of above methods.

- **Rebalancing Triggers**
  - **Skewed distribution**: some partitions have much more data than others. The distribution is not uniform (not evenly distributed) [overloaded]
  - **Hot spots**: a partition receives disproportionate query traffic. (hotspot) [overheated]

- **Rebalancing Methods**
  - Add new partitions and redistribute data.
  - Rebalance existing partitions (e.g., via consistent hashing).

- **Limitations / Trade-offs**
  - Cross-shard joins and aggregations are complex and slow.
  - Uneven workload distribution still possible if partitioning keys are poorly chosen.
  - Rebalancing data is costly and can cause downtime or high latency.
  - Directory-based sharding adds a dependency and risk of failure.

- Horizontal Partitioning (Sharding) – Quick Reference

```
                 ┌───────────────────────────┐
                 │     Horizontal Partition   │
                 │       (Sharding)           │
                 └───────────────────────────┘
                          │
        ┌─────────────────┼──────────────────┐
        │                 │                  │
        ▼                 ▼                  ▼
 ┌────────────┐    ┌───────────────┐    ┌─────────────────┐
 │ Hash-Based │    │ Range-Based   │    │ Directory-Based  │
 └────────────┘    └───────────────┘    └─────────────────┘
   - Even/random      - Predictable,       - Flexible
     distribution       simple ranges        (lookup table)
   - Minimizes hot    - Good for range     - Change logic
     spots              queries              w/o app change
   - Needs scatter-   - Risk of hot spots  - Single point of
     gather for         & skewed load        failure risk
     cross-shard       - Manual rebal.     - Extra latency
     queries
```

- **Trade-offs & Notes**
  - **Rebalancing** needed if data distribution becomes uneven or hot spots appear.
  - **Cross-shard queries** = higher latency (scatter-gather).
  - **Composite schemes** (e.g., Range + Hash) often used in practice.

- Prioritization – interviewers usually care most about:
  - *When to shard?* (when single DB is bottleneck)
  - *How to shard?* (range/hash/directory)
  - *Problems introduced?* (rebalancing, hotspots, cross-shard queries, joins)
  - *Solutions to problems?* (consistent hashing, lookup service, denormalization, query routing)

##### 6.2.2.2 Vertical Partitioning

- Structure: **definition → benefits → challenges → design considerations**, which matches how interviewers expect you to structure the explanation.

- Definition
  - Vertical partitioning splits a database by **columns** (or by functional grouping of features).
  - Related attributes are stored together on dedicated servers.
  - This reduces table width and allows more focused queries.
  - ? Vertical partitioning: manually partition; divide data to store tables (divide table to store its columns) related to a specific feature/need in their own servers;
    - Pro: straightforward to implement and low impact on application;
    - Con: additional growth->further partition, joining two tables in two separate Db can cause performance and consistency issues;
  - ??? Federation (functional partitioning) splits up databases by function, resulting in less read and write traffic to each database and therefore less replication lag;
    - Pro: the database is smaller, easier to fit in memory and cache; write in parallel, increasing throughput
    - Con: Update application logic to determine which database to read and write; join is more complex; more hardware and additional complexity.

- Benefits
  - **Straightforward** to implement, with relatively low impact on the application.
  - **Smaller datasets per DB** → easier to fit into memory/cache.
  - **Parallel writes** across partitions can improve throughput.
  - **Federation (functional partitioning):** splitting by business function reduces replication lag, balances load, and isolates workloads (e.g., separate DBs for users, orders, analytics).

- Challenges
  - **Complex joins & denormalization:** queries requiring data across partitions are slower and may cause consistency issues. A large number of logical partitions to accommodate future data growth, vs a few physical database server. Such database server can have multiple database instances running on it. Use a configuration file to map the logical partitions to database server. So that can move partitions around easily.
  - **Referential integrity:** foreign keys across partitions are difficult to enforce; must often be handled in application logic.
  - **Application changes:** logic must know which partition to query or write to.
  - **Rebalancing issues:**
    - Uneven load (overloaded/underloaded partitions, unbalanced).
    - Hotspots (too much activity concentrated on a partition).

- Design Considerations
  - **Logical vs Physical Partitions:**
    - Maintain more logical partitions than physical servers for flexibility. For better performance and scalability, we can keep more shard than these just required.
    - Use a configuration layer to map logical partitions to physical servers so they can be moved as load grows.
  - **Placement strategies:**
    - *Co-resident partitioning:* keep partitions on the same machine to reduce index size and I/O.
    - *Remote partitioning:* spread across machines to leverage more RAM, disk I/O, and network capacity.
  - **Data movement & balancing:**
    - Minimize re-sharding cost with **consistent hashing** or metadata lookup services.
  - **Load distribution:** aim for even spread to avoid hotspots.

##### 6.2.2.3 Horizontal vs Vertical Partitioning

| Aspect          | **Horizontal Partitioning (Sharding)**                                                                                                                                | **Vertical Partitioning**                                                                                                                                                                                 |
| --------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Definition**  | Splits a table by **rows** across multiple servers (e.g., users A–M on one DB, N–Z on another).                                                                       | Splits a table by **columns/features** (e.g., user profile fields on one DB, user preferences on another).                                                                                                |
| **Goal**        | Distribute data volume and queries evenly across servers to scale out.                                                                                                | Reduce table width, isolate workloads by feature, and improve manageability.                                                                                                                              |
| **Benefits**    | - Better scalability for large datasets. <br> - Allows parallel writes/reads across servers. <br> - Smaller index per shard → faster queries.                         | - Simple to implement initially. <br> - Smaller DB per partition → easier caching and fits in memory. <br> - Functional isolation (e.g., separate DBs by business module).                                |
| **Challenges**  | - Uneven distribution can cause hotspots. <br> - Rebalancing data when adding/removing servers is complex. <br> - Queries spanning shards require scatter-gather.     | - Cross-partition joins are expensive and complex. <br> - Referential integrity (foreign keys) often must be enforced at app level. <br> - Application logic needs awareness of which partition to query. |
| **When to Use** | - Extremely large datasets that cannot fit in a single DB. <br> - High throughput systems with heavy writes/reads. <br> - User-based partitioning (e.g., by user ID). | - Applications with clear functional boundaries (e.g., users, payments, logs). <br> - Reducing contention on wide tables. <br> - When scaling out by business domain is more natural than by row.         |
| **Example**     | Twitter user timeline: users are partitioned by ID hash across shards.                                                                                                | E-commerce: orders DB separate from payments DB.                                                                                                                                                          |

- Quick takeaway:
  - **Horizontal = scaling out rows** (good for *large datasets & parallelism*).
  - **Vertical = scaling out features/functions** (good for *isolation & modularity*).

### 6.3 Partitioning VS Sharding

#### 6.3.1 Partitioning

- **Definition**: Splitting **one large table inside a single database** into **smaller parts** for manageability and performance.
- **Scope**: Usually happens **inside a single database system** (same server or cluster).
- Managed by the **DB engine**
- **Types**:
  - **Horizontal partitioning**: rows split by range/hash/list (e.g., `UserID 1–1000 → partition A`).
  - **Vertical partitioning**: columns split into different tables (e.g., profile info vs authentication info).
- **Goal**: Manage **big tables** more efficiently → faster queries, better maintenance.
- Example: 
  - In Postgres, a `users` table is partitioned into `users_2024`, `users_2025` by `creation_date`. 
  - Or Postgres `users` table partitioned by `region_id` → still one DB.

#### 6.3.2 Sharding

- **Definition**: A **form of horizontal partitioning** where data is split across **multiple independent database servers/nodes (shards)**.
- **Scope**: Distributed systems, each shard is an independent DB instance with its own copy of schema.
- Managed by the **application or middleware layer**, not the DB engine alone.
- Goal: true horizontal scaling (support billions of rows/users).
- **Key feature**: Each shard handles a portion of the load → enables **horizontal scaling**.
- **Trade-offs**:
  - Pros: scales to billions of rows, parallel processing, removes bottleneck.
  - Cons: cross-shard queries are expensive, re-sharding is hard.
- Example: A global app splits users:
  - Shard 1 → users in North America
  - Shard 2 → users in Europe
  - Shard 3 → users in Asia

#### 6.3.3 Key Differences (Quick Recall)

| Aspect                    | Partitioning                    | Sharding                                       |
| ------------------------- | ------------------------------- | ---------------------------------------------- |
| **Where?**                | Within a single DB instance     | Across multiple DB servers                     |
| **Who manages?**          | The DB engine                   | The application / middleware                   |
| **Query**                  | Easy cross-partition joins      | Hard/expensive cross-shard joins               |
| **Use case**              | Handle large tables efficiently | Scale system horizontally to billions of users |
| **Cross-partition query** | Easy (same DB)                  | Hard/expensive (cross-shard joins)             |

- **Memory Hook:**
  - Partitioning = splitting tables inside a DB.
  - Sharding = partitioning data across multiple DBs.

#### 6.3.4 Comparison: Partitioning vs. Sharding

| **Aspect**         | **Partitioning**                                                                              | **Sharding**                                                                                               |
| ------------------ | --------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| **Definition**     | Splitting a single database (one DBMS instance) into logical/physical partitions.             | Splitting data across multiple independent databases (shards) on different servers.                        |
| **Scope**          | Within a single database server.                                                              | Across multiple database servers.                                                                          |
| **Management**     | Managed internally by the database system.                                                    | Requires application-level or middleware logic to route queries to the correct shard.                      |
| **Use Case**       | Optimizing large single-database performance (e.g., table partitioning in PostgreSQL, MySQL). | Scaling out when a single database server can’t handle the data volume or query load.                      |
| **Scalability**    | Limited (vertical scaling, still bound to one machine).                                       | High (horizontal scaling across many machines).                                                            |
| **Complexity**     | Low – transparent to applications, handled by DB engine.                                      | High – query routing, shard key design, and rebalancing are needed.                                        |
| **Failure Impact** | If the database fails, all partitions are affected (single point of failure).                 | A shard failure only affects part of the dataset (but requires careful HA design).                         |
| **Examples**       | Table partitioning by range, list, or hash inside MySQL/Postgres.                             | MongoDB sharding, Cassandra, custom shard key in MySQL/Postgres clusters.                                  |
| **Pros**           | • Simple to implement <br> • Efficient query pruning <br> • Managed by DB engine              | • Scales horizontally <br> • Reduces per-node data load <br> • Supports very large datasets                |
| **Cons**           | • Still tied to single-machine limits <br> • Doesn’t solve extreme scalability issues         | • More complex development & operations <br> • Harder joins across shards <br> • Rebalancing can be tricky |
| **Trade-offs**     | Good first step to improve single-node performance, but eventually hits machine limits.       | Higher scalability but adds significant complexity in design, operations, and consistency.                 |

- **Rule of thumb**
  - Use **Partitioning** if your workload is big but still fits on a single powerful server.
  - Use **Sharding** if you need to scale beyond a single machine.

- Takeaway:
  - Partitioning is a useful optimization within a single database, improving query performance and manageability without adding much complexity. However, it’s still bound by the limits of one machine. 
  - Sharding, on the other hand, distributes data across multiple servers to achieve true horizontal scalability. It enables handling massive datasets and traffic, but comes at the cost of more complex query routing, consistency management, and operational overhead. 
  - In practice, teams often start with partitioning, and move to sharding only when scale demands it.

## 7 Evaluation and Optimization

After finishing the design, compare it against the requirements and evaluate trade-offs. The goal is to identify gaps, acknowledge compromises, and suggest improvements.

### 7.1 Evaluation

- **Goal:** Ensure the system meets **non-functional** requirements.
- **What to evaluate:**
  - Availability
  - Scalability
  - Reliability
  - Consistency
  - Security & privacy
  - Fraud detection
  - Other non-functional requirements
- **How to evaluate:**
  - Review each component end-to-end (load balancer, CDN, web servers, application servers, databases, blob storage, caches).
  - Check how each component contributes to non-functional goals.

### 7.2 Security and Permissions

- **Privacy:** Protect user data.
- **Security:** Authentication, authorization, encryption, certificates.
- **Rate limiting / Throttling:** Prevent abuse, DoS, and traffic spikes.
  - Hard throttling → strict limit, excess requests dropped.
  - Soft throttling → small tolerance above limit.
  - Elastic throttling → dynamic limit if resources allow.
- **Compliance:** Handle international laws and regulations (e.g., content restrictions, GDPR).

### 7.3 Analytics (User Behavior)

- **Purpose:** Gain **insight into how users interact with the system**.
  1. Collect logs and metrics (requests, responses, session data).
  2. Analyze usage patterns (time of day, frequency, geography).
  3. Predict trends (e.g., load forecasting, feature adoption).
  4. Adapt system features or optimizations based on usage.

### 7.4 Monitoring and Telemetry

- **Purpose:** Provide **visibility into system health and performance**.
  - Track latency (per request) and throughput (aggregate).
  - Gather meaningful metrics (e.g., DAU, peak load, error rate, average latency).
  - Set up alerts for component failures or performance degradation.
  - Use monitoring insights to decide on scaling, caching, replication, or partitioning.

### 7.5 Bottleneck Identification and Mitigation

- **Goal:** Find and address weak points in the system.
  - Eliminate single points of failure.
  - Maintain enough replicas of data and services.
  - Continuously monitor and alert on degraded performance.
  - Apply techniques like load balancing, caching, partitioning, or replication to relieve bottlenecks.

### 7.6 **Sample Wrap-up Answer (concise, interview-style):** 2–3 minute spoken version

> To evaluate my design, I’d look at the **key non-functional requirements**: availability, scalability, reliability, and consistency. For example, I’d check whether replication and partitioning give us enough availability, and whether the caching and load balancer help us scale.
>
> On the **security side**, I’d enforce authentication and authorization, apply **rate limiting** to protect against abuse or DDoS, and also account for privacy and regional regulations like content restrictions.
>
> Next, I’d add **monitoring and analytics**. On the analytics side, I’d capture user behavior — things like peak traffic times and feature usage — to forecast growth and adapt capacity. On the monitoring side, I’d track latency, throughput, error rates, and set up alerts if any component degrades.
>
> Finally, I’d think about **bottlenecks** and mitigation: eliminate single points of failure with replication, ensure services have redundancy, and plan rebalancing if partitions or shards become unbalanced.
>
> Overall, the design balances **performance, reliability, and scalability**, and I’ve identified where trade-offs are needed, like extra replicas improving availability but adding cost.

---

⏱ This version takes about **2–3 minutes to speak** at a steady pace, and it hits all the categories from your note:

- Evaluation
- Security
- Analytics & Monitoring
- Bottlenecks / trade-offs

### 7.7 **1-Minute Wrap-up Answer:**

> To evaluate the design, I’d check the main non-functional goals: **availability, scalability, reliability, and consistency**. I’d ensure redundancy and partitioning to remove single points of failure, caching and load balancing for performance, and monitoring to track latency, throughput, and errors.
>
> On the **security side**, I’d enforce authentication, permissions, and **rate limiting** to defend against abuse. Finally, I’d add analytics and monitoring so we can understand user behavior, detect bottlenecks, and adjust capacity as the system grows.
>
### 7.8 Words in Interview

- “We’ve discussed the design. To evaluate: we need to ensure scalability via partitioning/sharding, availability via replication, security via authentication and rate limiting, monitoring for performance, and awareness of bottlenecks.”
- Just naming the categories (without deep-diving into each) usually takes 2 minutes and leaves a strong impression.

## 8 Trade-off

- Definition
  - When choose one solution, gain some advantages but also accept some disadvantages, compared to another solution.
  - It’s not just pros/cons in isolation, but rather **what to give up in order to get something else, and why that decision fits the requirements**.
  - The “trade-off” here isn’t just listing pros/cons, but showing the reasoning: **Why one matters more in context of the requirements.**

- Goal
  - Every design choice comes with trade-offs. The goal is to choose the solution whose trade-offs do not severely impact the **most important requirements** of the system.

- Steps
  1. Explore alternative solutions.
  2. Identify and explain their major trade-offs.
  3. Make **informed** decisions to balance those trade-offs against **requirements**.

- **Considerations**: Trade-offs should **be evaluated in the context of** (considering the requirements of the system):
  - User needs
  - Business goals
  - Prioritized use cases
  - Conflicting requirements
  - Resource limitations
  - Design constraints

- How to Think About Trade-offs (Interview Framework): Whenever you discuss a design choice, ask:
  - **Reliability** – Does it risk downtime or data loss?
  - **Performance** – Does it make things faster? Does it increase latency?
  - **Scalability** – Can it handle more users/data easily?
  - **Security / Privacy** – Does it leak data or make guessing easier?
  - **Complexity** – Is it harder to build/maintain?
  - **Cost** – Does it need more servers, more storage, higher $$$?
  - **Every trade-off is some balance among these dimensions.**

- when the step says: **“Identify and explain their major trade-offs”**, what the interviewer expects is:
  - Show you know there’s **no perfect solution**.
  - Show you can **compare alternatives in terms of the 5–6 dimensions above**.
  - Show you can **decide based on requirements, not just list pros/cons**.

- **Trade-off Checklist for System Design Interviews**: Whenever you compare two (or more) design choices, walk through these dimensions:
  - **Reliability & Availability**
    - ✅ Does this design avoid single points of failure?
    - ✅ Can it survive machine crashes or network failures?
    - ⚠️ How much replication is needed?
  
  - **Performance**
    - ✅ Does this reduce latency? (speed of one request)
    - ✅ Does this improve throughput? (number of requests per second)
    - ⚠️ Does it create new bottlenecks?

  - **Scalability**
    - ✅ How well does it handle growth in users/data?
    - ✅ Is horizontal scaling (adding machines) easy or hard?
    - ⚠️ Will it require complex sharding or partitioning?

  - **Consistency**
    - ✅ Do we get strong consistency (always correct data)?
    - ✅ Or eventual consistency (faster, but may be stale)?
    - ⚠️ Which matters more for this system’s requirements?

  - **Security / Privacy**
    - ✅ Does it prevent abuse (guessable IDs, spam, fraud)?
    - ✅ Does it align with compliance/regulations (GDPR, HIPAA)?
    - ⚠️ Any risks of exposing sensitive data?

  - **Complexity**
    - ✅ Is it easy to implement and maintain?
    - ✅ Do engineers/operators need deep expertise to manage it?
    - ⚠️ Does it add operational burden (e.g., more moving parts)?

  - **Cost**
    - ✅ Does it save infra cost (CPU, memory, storage)?
    - ⚠️ Does it require expensive infra (SSD, GPU, lots of servers)?
    - ⚠️ Does it increase developer/Ops cost?

- Example Use (Quick 30-second answer in interview): **Q:** Should we use SQL or NoSQL for storing user profiles?
  - **Answer (using checklist):**
    - **Reliability:** Both can be made highly available, but SQL has mature replication.
    - **Performance:** SQL gives strong query flexibility; NoSQL gives faster writes at scale.
    - **Scalability:** NoSQL scales horizontally more easily. SQL requires sharding earlier.
    - **Consistency:** SQL = strong consistency; NoSQL = eventual consistency by default.
    - **Security:** Both support security, but SQL tends to have more built-in features.
    - **Complexity:** SQL is simpler for structured data and joins; NoSQL is better for unstructured/large scale.
    - **Cost:** At small scale SQL is cheaper; at huge scale NoSQL may reduce infra cost.
  - **Decision:** If we expect **billions of users and simple profile schema**, lean toward **NoSQL**. If we need **complex queries + strong consistency**, lean toward **SQL**.
  - This way, you don’t just say “SQL is consistent, NoSQL is scalable.” You show you can **evaluate trade-offs systematically** and **tie them back to requirements**.

### 8.1 Common Trade-offs

- **Consistency vs Availability**
  - Strong consistency reduces availability; prioritizing availability often leads to eventual consistency. choose based on business requirements in case of network partition
  - Example: WhatsApp may prioritize consistency over availability in message delivery.
- **Performance vs Scalability**
  - Complex data structures improve performance but may limit scalability.
- **Data Integrity vs Performance**
  - Strong constraints ensure integrity but slow down write-heavy systems.
- **Short-Term vs Long-Term Goals**
  - Quick solutions may create technical debt; sustainable solutions may delay delivery.
- **Reliability vs Cost**
  - More replicas improve reliability but increase infrastructure cost.
- **Security vs Usability**
  - Stricter security makes user experience less convenient.
- **Security vs Latency**
  - Encryption adds latency; WhatsApp prioritizes security over minimal latency.
- **Monolithic vs Microservices**
  - Monolithic: simpler, faster to build, but harder to scale/fault isolate.
  - Microservices: scalable and fault-tolerant, but complex in deployment and communication.
- **Real-time vs Batch Processing**
  - Real-time is immediate but costly; batch is cheaper but delayed.
- **Normalization vs Denormalization**
  - Normalization reduces redundancy but slows some queries.
  - Denormalization speeds queries but risks inconsistency.
- **Caching vs Freshness**
  - Cache improves speed but risks stale data.
- **Centralized vs Decentralized Control**
  - Centralization simplifies management but risks single point of failure.
  - Decentralization increases resilience but may cause inconsistency.

### 8.2 Partitioning Trade-offs

- **User ID partitioning**
  - ✅ Enables user-specific transactions
  - ❌ Hotspots: one user with heavy activity overloads a partition; all of a user’s data unavailable if their partition fails
- **Tweet/Item ID partitioning**
  - ✅ Evenly distributed across servers (e.g., even/odd ID split)
  - ❌ Hard to run batch operations across ranges
- **Creation Time partitioning**
  - ✅ Supports time-based queries naturally
  - ❌ Risk of uneven distribution if traffic spikes at certain times
- **Hybrid (e.g., Tweet ID + Timestamp)**
  - ✅ Better distribution and avoids hotspots
- **Partitioning schemes**: range-based, hash-based, or hybrid
- **Database choice**: SQL vs NoSQL (transactional integrity vs horizontal scalability)

### 8.3 User Connections: HTTP vs WebSocket

- **HTTP (Polling)**
  - Short/long polling: client repeatedly asks for updates. client <- bandwidth -> server: have a delay on client, waste bandwidth, keep the server busy;
  - ❌ Delays, bandwidth waste, higher server load.
- **WebSocket**
  - Persistent, bidirectional connection.
  - ✅ Real-time updates with lower overhead.
  - ❌ Requires more server resources per connection.

### 8.4 CDN: Push vs Pull

- **Pull CDN**
  - Content fetched from origin on first request; cached afterward.
  - ✅ Simpler to configure, less storage needed.
  - ✅ Better for dynamic/frequently updated content, and a high traffic load.
  - ❌ First request is slower.
- **Push CDN**
  - Content preloaded into CDN nodes.
  - ✅ Faster for static content, fewer cache misses.
  - ❌ Requires more replicas and storage, manual upload/config.
- **Rule of thumb**:
  - Heavy traffic → Pull CDN
  - Low/medium traffic or static content → Push CDN

### 8.5 Newsfeed: Push vs Pull (Fanout Models)

- **Push (Fanout-on-Write)**
  - Posts are pushed to all followers immediately.
  - ✅ Real-time updates.
  - ❌ Not scalable for celebrities with millions of followers.
- **Pull (Fanout-on-Load)**
  - Posts are fetched when a user loads their feed.
  - ✅ Scales better for high-fanout users.
  - ❌ Feeds may be stale; wasted queries when no updates exist.
- **Hybrid**
  - Push updates for most users.
  - Pull for high-fanout users or when updates are frequent.
  - Sometimes: push notifications → pull feed content.

## 9 System Design Principles

### 9.1 Prioritized System Design Principles (for large-scale/distributed systems)

- **1. Scalability**
  - First priority: can the system handle future growth?
  - Interviewers want to see if you design beyond the “toy” version.

- **2. Reliability & Fault Tolerance**
  - A system must still function despite hardware, network, or software failures.
  - Reliability keeps user trust; downtime or data loss is often worse than slowness.

- **3. Availability**
  - Users expect the system to be **up nearly all the time** (e.g., “five nines” SLA).
  - Often goes hand-in-hand with reliability, but availability focuses on uptime.

- **4. Performance (Latency & Throughput)**
  - After scaling and reliability, the next priority is **speed**.
  - Users tolerate some errors more than they tolerate slowness.

- **5. Consistency (Data Correctness)**
  - Data must make sense (no missing transactions, no duplicate orders).
  - Trade-offs with availability (CAP theorem), so it’s not always #1.

- **6. Security & Privacy**
  - Always important, but in interviews often assumed unless the question is security-focused.
  - Still: mention authentication, authorization, encryption, and compliance.

- **7. Cost Efficiency**
  - Comes after functional goals are met.
  - Optimize infra cost, storage, replication, and cloud spend.

- **8. Simplicity & Maintainability**
  - Simpler systems are easier to operate and evolve.
  - Important but secondary in interviews: complexity is sometimes excused for scale.
  
- **9. Observability (Monitoring & Logging)**
  - Enables performance tuning, debugging, incident response.
  - Crucial in real systems, but in a 45-min interview often mentioned last.

- **10. Graceful Degradation & Resilience**
  - Bonus points in interviews if you mention “system still works partially under failure.”
  - Often part of reliability, but good to explicitly mention.

- **Why this order?**
  - **Top 4 (Scalability, Reliability, Availability, Performance)** = what interviewers care most about.
  - **Middle (Consistency, Security, Cost)** = depend on business requirements.
  - **Last (Simplicity, Observability, Resilience)** = valuable, but rarely the primary design driver in interview settings.

### 9.2 Inaccurate Principles (Most are OOD in fact)

System design principles are **fundamental guidelines** and concepts that help software engineers and architects create effective, efficient, and maintainable software systems. These principles provide **a framework for making decisions about the architecture, structure, and behavior of a system**. They aim to ensure that the resulting system meets both its functional and non-functional requirements while **being adaptable to changes and scalable**. Here are some key system design principles:

1. **Modularity and Separation of Concerns**:
   - Divide the system into smaller, manageable modules with distinct responsibilities.
   - Each module should focus on a single aspect or concern of the system.

2. **Abstraction**:
   - Hide complex implementation details behind well-defined interfaces.
   - Abstractions make components easier to use, understand, and modify.

3. **Encapsulation**:
   - Restrict access to internal details of a component and expose only necessary functionalities.
   - Encapsulation promotes information hiding and helps manage complexity.

4. **Single Responsibility Principle (SRP)**: 4-8 are **SOLID Principles (OOD)**
   - Each module or class should have a single reason to change.
   - Promotes maintainability by reducing the impact of changes.

5. **Open/Closed Principle (OCP)**:
   - Software entities (classes, modules) should be open for extension but closed for modification.
   - Encourages designing systems that can be easily extended without altering existing code.

6. **Dependency Inversion Principle (DIP)**:
   - Depend on abstractions rather than concrete implementations.
   - Helps reduce coupling between components and promotes flexibility.

7. **Liskov Substitution Principle (LSP)**:
   - Objects of a derived class should be substitutable for objects of the base class without affecting program correctness.
   - Ensures that derived classes adhere to the behavior expected by clients.

8. **Interface Segregation Principle (ISP)**:
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
    - Divide a system into distinct sections that address different aspects (e.g., user interface, business logic, data storage).
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

## 10 System Design Best Practices

System design best practices are guidelines and strategies that help software architects and engineers create high-quality, efficient, scalable, and maintainable software systems. These practices are based on industry experience and lessons learned, aiming to ensure that the resulting systems meet both functional and non-functional requirements. Here are some key system design best practices:

1. **Understand Requirements**:
   - Thoroughly understand the requirements of the system before beginning the design process.
   - **Engage with stakeholders** to **gather and clarify** requirements.

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

14. **Performance Profiling and Optimization**: (Important)
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

## 11 Scale

### 11.1 Load Balancers & its algorithms - How to scale web servers (reverse proxy)

LB helps to

- Scaling
  1. spread the traffic across a cluster of servers; facilitate scaling either up or down
- Availability
  1. prevent a single point of failures,  
  2. improve overall responsiveness and availability of application, websites or databases,
- Performance
  1. achieve maximum throughput;
  2. minimize response time (latency)
  3. improve overall responsiveness and availability of application, websites or databases,
- Others
  1. optimize resource usage (avoid overload and under-load of any machine);  
  2. keeps tracks of the status of all the resources;

- Note
  - To utilize full scalability and redundancy, try to balance the load at each layer of the system;
  - faster, higher throughput, easier for administrators, predictive analytics to determine traffic bottlenecks, give actionable insights to automation and help drive business decisions.
  - LB helps scale horizontally across an ever-increasing number of servers.

#### Metrics

- Active Connections (session affinity or sticky session)
- Latency
- Bandwidth (throughput)
- Random (Round Robin or Hash)

#### Algorithm Categories

- Static vs Dynamic
  - Static (simple, based on the server's configuration) [RR, weighted, IP hash]
  - Dynamic (complex, but better; consider the current state and healthy of the servers) [LCM, LRM, LBM]
- Stateful vs Stateless
  - Stateful: complex; maintain the state of the sessions established between clients and hosting servers; share the state information among load balancers
  - Stateless: faster and lightweight; use consistent hashing
- Implementation
  - Hardware (expensive): can handle concurrent users; poor availability; high cost and less flexible
  - Software. e.g HAProxy (layer 4 or 7), NGINX; flexibility, programmability, and cost-effectiveness; predictive analysis
- Layers:
  - Layer 4 - transport layer (TCP/UDP); faster; source and destination IP, port; maintain connection/session
  - Layer 7 - application layer; make application-aware forwarding decisions based on HTTP headers, URLs, message, cookies and other application-specific data like user ID; can take responsibilities like limiting user, HTTP routing, and header rewriting
- Multiple tiers
  - tier - 0 or 1: based on IP, use RR and Weighted RR
  - tier - 2: layer 4 LB; maintain connections/sessions; consistent hashing;
  - tier - 3: layer 7 LB; enable scalability and provide high availability; offload TLS/SSL

#### algorithms

- The choice of algorithm depends on the specific needs and characteristics of the system and the workload being handled
- Least connection Method, LCM (servers with fewest active connections)
- Least Response Time Method, LRM (servers with lowest average response time)
- Least Bandwidth Method, LBM (lowest MB/s traffic)
- Round Robin: does not take server load into consideration, RR; can overloaded
- Weighted Round Robin Method, WRR
- IP Hash (IP Address affinity)
- Random : Simple to implement and no overhead
- By HTTP Header or URL
- By request parameters of the query string

Con:
  a. performance bottleneck, if it does not have enough resources or it is not configured properly
  b. increase the complexity (be stateless, session can be stored in a centralized data store)
  c, single point of failure

### 11.2 Caching - How to scale database?  Caching or vertically and horizontally

- Cache the DB results adding an extra caching layer between the servers and the database
- A cache is a key-value store that reside between applications and data storage;
- Redis is persistent while memcache scales well.

**Benefit**

- Cache will enable you to make vastly better use of the resources you already have as well as making otherwise unattainable product requirements feasible.
- Can exist at all levels in architecture, but are often found at the level nearest to the front end, where they are implemented to return data quickly without taxing downstream levels.
- What should be cached?
  - long-running queries on databases;
  - high-latency network requests (for external APIs),
  - computation-intensive processing;

**Disadvantages**:

- main consistency between caches and the source of truth (database) through cache invalidation which is difficult; need to make application changes
- Caching works well with static data by saving time and increasing speed, but not well with mutable or dynamic, for need to make sure that the cached data is in sync

**CDN (Content Delivery Network)** are a kind of cache that comes into play for sites serving large amounts of static media. Can replicate content in multiple places, based on user's geographic location and the original of the webpage; security improvement, increase in content availability and redundancy, better load times, low bandwidth cost.  

- type: Push and Pull, referring the data streaming upload and download???

#### Cache eviction policies

- Definition: Eviction policy determines how the cache handles the replacement of old data with new data when the cache is full
- **Policies**: Order (first vs last), Recently (time: least vs most), Frequency (least), Random;

- Order
  - First In First Out (FIFO), time-serious ???
  - Last In First Out (LIFO)
- Recent
  - Least Recently Used (LRU), suitable for long-tailed
  - Most Recently Used (MRU)
- Frequency
  - Least Frequently Used (LFU)
- Random Replacement (RR)

#### Cache expiration

Determine how long data is kept in the cache before it is considered stale and is removed.
A shorter expiration time can improve the freshness of the data, but increase the number of accesses to the underlying data source

#### Cache strategy (Invalidation)

Cache Invalidation: keep the cache coherent with the source of data (e.g. database);  
strategy: cache and permanent story like disk or database, write only one or both; depend on the data and data access patterns (how data is written and read)  
metrics: read-intensive vs write-intensive (write-write, write-reread); latency and throughput; consistency and data loss;   

- Cache aside: general purpose, work best for read-heavy workloads; usually write-around, use write-through or Time To Live(TTL) to invalidate cache in order to avoid the stale data; The application is responsible for reading and writing from the storage. The cache does not interact with storage directly. Application load the entry from database, add it to cache and then return it to user. Lazy loading. Only requested data is cached.   
- Read-through  
- Write-through (both): data is written into both cache and database simultaneously. The application uses the cache as the main data store, reading and writing data to it, while the cache is responsible for reading and writing to the database synchronously. pros: fast retrieval, consistency between cache and storage, minimizes the risk of data loss; cons: higher latency for write operation; data written might never be read.   
- Write-around (storage only): data is written into the permanent storage only (bypassing the cache). pros: cache is not flooded with written operation which is not subsequently be re-read. con: higher latency for the recently written data, for cache-miss, so higher latency;    
- Write-back (write-behind)(cache only): the data is written to cache alone; asynchronously write entry to the data store. pros: low-latency and high-throughput for write-intensive applications. con: risk of data loss; more complex to implement, for its asynchronously writing.   

### 11.3 CDN -> How to prepare our assets to deliver faster across the world?

Real-time and low-latency require

- Replication of servers and server's location close to users (CDN) 
- PULL vs PUSH: real-time (VOIP, video, notification system and real-time feeds) : push (message queue), not pull(expensive in bandwidth and unnecessary load on Servers and DB, not scalable)

### 11.4 Cache, Scale, and Shard result

#### cache result==> low latency, high throughput and high available (if db server is down for a while)

caching will enable you to make vastly better use of the resources you already have; 
application caching, database caching (need tweaking the configuration), in-memory caches

In-memory caches: 
precalculated results, pre-generating expensive indexes, storing copies of frequently accessed data in a faster backend

#### Scalability result ==> low-latency and fault-tolerant by replicate (deal with lower performance)

Scalability methods—With the architecture, there are many techniques and methods which can be used in order to customize and improve the design of a system. 
Some of the most widely used are: redundancy, partitioning, caching, indexing, load balancing, and queues.

#### Shard result==> high performance by destructing the load and high available, and latency-free

## 12 Components

every building block in system design has functional and nonfunctional requirements that must be met.

### Load Balancers

Evenly distributing the computational load allows for faster response times and the capacity for more web traffic.

- Scaling: Load balancers facilitate scaling, either up or down, by disguising changes made to the number of servers.
- Availability: By dividing requests, load balancers maintain availability of the system even in the event of a server outage.
- Performance: Directing requests to servers with low traffic decreases response time for the end user.

Load balancers are the unsung heroes of scalable systems — distributing incoming traffic, boosting reliability, and ensuring performance stays smooth, even when demand spikes.

### Key Value Stores

Similar to Hash table or dictionaries. Store information as a pair in the Key and Value format, for easy retrieval. Distributed hash tables (DHT). 
e.g. AWS DynamoDB, AWS ElastiCache (a managed in-memory data store serivce which supports caching, like Redis or Memcached) (Redis, in particular, supports advanced data structures and features that make it effective for caching.
When it comes to caching user information effectively, Amazon ElastiCache with Redis is often a preferred choice due to its advanced caching capabilities, data structures, and support for use cases like user sessions and frequently accessed data.  However, the choice of service will depend on factors such as the complexity of the data, required data structures, access patterns, and performance requirements. 

### Blob Storage

Blob: Binary Large Object; a storage solution for unstructured data, such as photos, audios, multimedia, executable code; uses flat data organization pattern without hierarchy 
The main rule: write once, read many or WORM. Ensure the important dat is protected since once the data is written, it can be read, but not changed. 
e.g. AWS S3

### Database

A database is an organized collection of data that can be easily accessed and modified; make the process of storing, retrieving, modifying, and deleting data simpler. SQL vs NoSQL 

### Rate Limiters

It sets a limit for the numbers of requests a service will fulfill. It will throttle requests that cross this threshold.
It is an important line of defense for services and system; prevent services being flooded with requests; mitigate resource consumption.
e.g. AWS API Gateway(built-in rate limiting on request/API/method per second/minute/others), AWS WAF(Web Application Firewall, restrict requests from the specific IP address or IP address ranges); 
AWS Lambda, AWS CloudFront (CDN, request rate limiting to prevent abuse and ensure a smooth experience for users), AWS ELB(Elastic Load Balancing, configure specific rules as rate limiting)

### Monitoring Systems

It is a software that allow system administrators to monitor infrastructure. It creates one centralized location for observing the overall performance of a potentially large system of computers in real time. 
It can monitor: CPU, memory, bandwidth, routers, switches, applications, etc. e.g. AWS CloudWatch; AWS CloudTrail, X-Ray, Inspector, Trusted Advisor, and Config

### Distributed messaging queues

A producer creates messages and consumers receive and process them. 
* Improve performance through asynchronous communication since producers and consumers act independently of each other
* Decouple or reduce dependency in the system
* Improve reliability and allow simpler and less cluttered system design 
* Asynchronous messaging facilitates scalability, for more consumers can be added to compensate for the increased load
  
Usage: 
 * Sending emails
 * Data post-processing: It can reduce end-user latency, by enabling offline time-consuming and resource-intensive process, such as processing image, video, multimedia to different format or platforms
 * Recommender systems: use cookies to personalize a user’s content; retrieves the user data and processes it. A messaging queue can be incorporated to make this process more efficient as background data processing can be time consuming.

### Distributed unique ID generators

It is important to tag entities in a system with a unique identifier. Millions of events may occur every second in a large distributed system, so we need a method of distinguishing them. A unique ID generator performs this task and enables the logging and tracking of event flows for debugging or maintenance purposes.
In most cases this is a universal unique ID (UUID). These are 128 bit numbers
Range handlers feature multiple servers that each cover a range of ID values.

### Distributed search
Search systems are composed of three main entities: 
* Crawler: finds/fetches content and creates documents
* Indexer: builds a searchable index
* Searcher: runs the search query against the index
Distributed search systems are reliable and ideal for horizontal scalability
E.g. Elasticsearch 

### Distributed logging services
Logging is the process of recording data, in particular the events that occur in a software system. A log file may document service actions, transactions, microservices, or any other data that may be helpful when debugging. 
Logging in a microservice architecture is convenient because the logs can be traced along a flow of events from end-to-end. Since microservices can create interdependencies in a system, and a failure of one service can cascade to others, logging helps to determine the root cause of the failure.
e.g. AWS CloudWatch logs: Centralized Log Storage, Scalable and Distributed, Real-Time Monitoring, Search and Query, Retention and Archiving, Integration with Other AWS Services, Access Control and Security, CloudWatch Metrics Integration, Automated Actions 

### Distributed task schedulers
A **task** is a unit of work that requires computational resources, like CPU time, memory, storage, and network bandwidth, for some specified amount of time.
It is important for tasks like image uploading or social media posting to be asynchronous as to not hold the user waiting for background tasks to end.
Task schedulers mediate the supply-demand balance between tasks and resources to control the workflow of the system. By allocating resources task schedulers can ensure that task-level and system-level goals are met in an efficient manner. It is widely used in systems like Cloud Computing Services, Large Distributed Systems, and Single-OS-base nodes

### Automation: The Self-Healing System
Automation is the engine that keeps a large system stable and cost-efficient.

- Auto-Scaling: This is the most critical function. It uses Aggregated Metrics (like CPU usage across the web tier) to automatically:
- Add new web servers when traffic spikes (scaling out).
- Remove idle web servers when traffic drops (saving cost).
- Automated Failovers: Tools that automatically promote a Slave DB to Master DB during a failure, or switch traffic from DC1 to DC2 during an outage.
- Deployment & Testing: Automated tools that deploy new code and run health checks across hundreds of servers simultaneously, minimizing human error.

### Others
* Domain Name System (DNS)
* Content Delivery Network (CDN)
* Distributed Caching
* Publish-Subscribe System
* Sharded Counters

## 13 Common Design patterns

### 13.1 Microservices

An application is broken down into a collection of small, independent services that communicate with each other over a network. Each service is responsible for a specific functionality and is developed, deployed, and scaled independently.
Pro: increased scalability, improved fault tolerance, and faster deployment cycles.
Con: additional complexity, such as service discovery and inter-service communication;

### 13.2 Event Sourcing

the state of an application is represented as a stream of events, rather than a snapshot of its current state. This pattern is often used in systems that need to handle a large number of concurrent updates, such as financial systems and gaming platforms.
Pro: easy replay of events, which can be useful for debugging and auditing
Con: requires additional storage and computational resources to maintain the event stream

### 13.3 CQRS (Command Query Responsibility Segregation)

- Definition: separates the read and write operations of a system into separate models, allowing for optimized performance and scalability. This pattern can be useful in systems that handle a high volume of read and write operations, such as e-commerce websites
- Pro: allows for different data stores and caching strategies to be used for read and write operations, improving the performance of both
- Con: requires more complex design and more effort to maintain two separate models of the data.

### 13.4 Circuit Breaker

can be used to prevent cascading failures in a distributed system. It works by monitoring the health of a service and, when it detects an issue, it “trips” and prevents further requests from being sent to that service.  
Pro: This helps to prevent a single point of failure from bringing down the entire system.

### 13.5 Backpressure

used to control the rate at which data is processed in a system, preventing it from being overwhelmed. This can be done by buffering incoming data and only processing it at a specific rate, or by rejecting incoming data if the system is unable to handle it.

## 14 Q&A

### Single point of failure require--> Redundancy and Replication
HA Architecture - Micro services 

**Redundancy**: the duplication of critical components or functions of a system with the intention of increasing the reliability of the system and to improve actual system performance. 
Widely used in DBMS, usually with a primary-replica relationship between the original and the copies. The primary server gets all the updates, which then ripple through to the replica servers.

**Replication**: sharing information to ensure consistency between redundant resources (e.g. SW or HW), to improve reliability, fault-tolerance, or accessibility.

**Highly Availability Mode**: improve reliability, fault-tolerance, or accessibility
* Redundancy  - Active-passive	HA mode (remove the single point of failure and provides backup in case a crisis by failover)
* Replication - Active-active		HA mode 

**Failover** 
(con: more hardware and additional complexity, the potential for loss of data)
* Active-passive (master-slave failover, the passive is hot/cold standby)
* Active-active (master-master failover)

Need to ensure consistency 
Also provide a backup or spare functionality if needed in a crisis 

message queue to queue all requests, so that the system is highly available and open to updates while remaining the consistent at the same time

**Redundancy** - describes the fact that you have more than one node/component/process in a system and it's pretty useful for handling failovers. In the case that one of your nodes fail, another node in the system can take over and carry on. 
Redundancy can be:
* active - where all the traffic goes to all nodes at the same time
* passive - where one node receive traffic and in the case of failure, a switch will be made to another node.
"Redundancy is the duplication of nodes, in case of some of them are failing"

**Replication** - includes redundancy, but involves the copying of data from one node to another or the synchronization of state between nodes. An example of where replication is done is at the databases or MQs level that forms a cluster. 
Replication can be:
* active: each node receives each message in order to keep in sync with the rest of the nodes
* passive: this is the leader-follower model, where the leader receives all the requests and then forwards them to the followers.
"Replication is the synchronization of state between redundant nodes."

**Redundancy** : Duplication of critical components (node, process) with the aim to achieve reliability. Redundancy helps avoid single-point failure. For instance, if we have two instances running and one of them fails then, then the system can switch over to another one.

**Replication** : Sharing information to ensure consistency between redundant resources.

Great question 👌 These two often come together but mean very different things:

---

**Authentication**

- **What it is:** The process of **proving your identity** to the system.
- **Goal:** Answer the question **“Who are you?”**
- **How:** Credentials or factors such as:
  - Username + password
  - OTP (One-Time Password, SMS/Email code)
  - Biometrics (fingerprint, face scan)
  - OAuth tokens (Google login, Facebook login)

✅ If successful, the system knows *you are indeed who you claim to be.*

---

**Authorization**

- **What it is:** The process of **determining what you are allowed to do** after you are authenticated.
- **Goal:** Answer the question **“What can you do?”**
- **How:** Rules, policies, or access control:
  - Role-based access control (RBAC) → e.g., Admin vs User
  - Attribute-based access control (ABAC) → permissions based on attributes like department, location
  - Access control lists (ACLs)

✅ If successful, the system grants access only to resources or actions you are permitted to use.

---

**Key Difference**

| Aspect             | Authentication                     | Authorization                               |
| ------------------ | ---------------------------------- | ------------------------------------------- |
| **Definition**     | Verifies identity                  | Grants/denies access rights                 |
| **Question**       | "Who are you?"                     | "What are you allowed to do?"               |
| **Happens**        | First                              | After authentication                        |
| **Implementation** | Passwords, OTPs, biometrics, OAuth | RBAC, ACLs, policy checks                   |
| **Example**        | Logging in with email + password   | Admin can delete a user, normal user cannot |

---

**Analogy**

- **Authentication** = Showing your **passport** at airport security (prove who you are).
- **Authorization** = Checking your **boarding pass** (decides which plane/seat you’re allowed on).

---

Would you like me to also show **how authentication & authorization fit into a system design** (e.g., API Gateway, Auth service, DB)?


### Checkpointing <-- Fault Tolerance
Each server performs checkpointing periodically and dump a snapshot to all its data onto a remote server. This will ensure that if a sever dies down, another server can replace it by taking its data from the last snapshot. 

### Fault Tolerance -> Checkpointing, Load Balancer, Replication

### Asynchronism
pre-render massive framework dynamic content into static HTML files and store to Amazon S3 or content delivery network. This would make website super fast(handle millions of request per sec) 
A script would do this job and would be called by cronjob every hour. This was one way of doing asynchronism.
If a user requests for a computation-intensive task, the front end of the website sends the job to the job queue and signals back to the user and lets the user browse the website meanwhile. 
As soon as the frontend is signaled about “job is done”, the frontend notifies the user about it.

Synchronous Communication
* Immediate response is crucial
* Low latency is required
* Services are tightly coupled
* Simplicity in control flow is preferred
* Asynchronous Communication

Services need to work independently
* Decoupling is necessary to ensure fault tolerance
* Scalability and responsiveness are crucial
* Latency can be tolerated

Synchronous and asynchronous communication patterns play vital roles in microservices architecture. 
* While synchronous communication offers simplicity and immediate results, it can also introduce potential blocking and performance issues. 
* On the other hand, asynchronous communication provides decoupling, better fault tolerance, and scalability, albeit at the cost of increased complexity.

### Extensibility 
Our service should be designed to in a modular way with the expectation that new functionality will be added to it. 

Facebook System Design
https://www.youtube.com/watch?v=hykjbT5Z0oE&t=1041s

### Ranking
* Involves multiple advanced ranking and recommendation algorithms; it is a computationally intensive task
* Consist of big-data processing systems that might utilize specialized hardware like graphics processing units (GPUs) and tensor processing units (TPUs)
* Factor: a reference count, freshness, user's previous history, likes, dislikes, shares, comments, clicks, user location, language, personal history, demographics
* Consider all these factors to predict relevant and important posts for a user
* Select out a few top posts from a group of candidate posts based on the assigned scores
* Sort and display these selected posts in decreasing order of the assigned scores 

### Recommendation
* Base on users' profiles, and also consider their interests, view and search history, subscribed channels, related topics, and activities such as comments and likes
* Use machine learning in choosing/generating/filtering the candidates and ranking them according to user's interests and history. 

### Popular services: 
Distributed cache: Redis
Search Index : Elastic
Message queue : Kafka
Databases NoSql : HBase
Databases Relational: MySql

### Interview tool
Facebook offered me three choices - Google Drawings,
BlueJeans Whiteboard, or ScreenShare your choice


### Questions: 
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

## 15 Future + ML 
1. Use two dimensions time and space for a topic. e.g. Netflix
2. Synchronize post by topics
3. Allow to take a deep dive into the particular topic. e.g. Netflix
4. Create an audio narrator based on AI + ML 
5. Offer the suggestion or possibility on true or false for the news/source
6. Provider both positive and negative on the same topic; can configure the percentage
7. Can follow up some topics a few days after first reviewing and get more new information about it

## 16 Review, Evaluate, and Evolve
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

## 17 Interview Framework

### 17.1 Framework

1. **Functional Requirements (10m)**
   1.0. NOTE: from external to internal; Users -> Actions/APIs -> System
   1.1. Users
   1.2. Core APIs (CRUD & Actions) (User's perspective/Actions)
   1.3. System
   1.4. Data (Evens/Logs; No direct user involved)
   - NOTE:
     - User and System (Service) interaction (request and response)
     - User as external and System (Service) as internal
     - Interaction (request and response) between external and internal
     - Similar to User -> Public API (Core APIs) -> Class (System/Service)

2. **Non-functional Requirements**
   2.1. Availability
   2.2. Reliability (durable, no data lost)
   2.3. Performance (Latency and Throughput target)
   2.4. Scalability
   2.5. Consistency
   2.6. Security
   2.7. Observability
   - General-purpose consumer internet systems priority:
     - Availability > Reliability > Scalability > Performance > Security > Consistency > Observability
     - This ordering emphasizes availability first, then correctness (reliability), followed by growth (scalability) and user experience (performance), while still showing awareness of security, consistency, and observability.
   - Finance/healthcare priority (correctness first):
     - Reliability > Consistency > Security > Availability > Performance > Scalability > Observability
   - mainly Security (preventing abuse) — secondarily Reliability and Performance: Might need to limit the amount of text/image user can upload to stop the abuse of the service

3. **Quantitative Analysis (Back-of-the-Envelope Estimation on Scale)**
   3.1. Users: Users & DAU
   3.2. Actions: Read vs Write (ratio)
   3.3. Traffics: QPS / TPS (R/W) (average, peak: QPS (x 3))
   3.4. Data: Storage (write) (= # of object x size) (growth, margin, replica/backup)
   3.5. Transports: Bandwidth (write & read) (income/ingress & outcome/egress) (= QPS * object size)
   3.6. Costs: Servers (read replica)
   3.7. CPU & Memory (Cache Memory for read)

4. **High-level Design + Data Flow (5–10m)**
   4.1. Building Blocks (Components: LB, API GW, servers, DB, blobs)
   4.2. Workflow

5. **APIs Design**
   5.1. API types
   5.2. Actions, parameter returns;

6. **Data Schema + Data Store**
   6.1. SQL vs NoSQL
   6.2. Object Storage
   6.3. DB Partitioning / Sharding

7. **Deep Dive (10m)**
   7.1. Scale
   7.2. Partition and Replication
   7.3. VPC
   7.4. Authentication, Throttling, Load Balancing
   7.5. Push vs Pull

8. **Evolve and Optimize (5m)**
   8.1. Single Point of Failure
   8.2. Monitoring and Logging (diagnosing and debugging)
   8.3. Bottleneck
   8.4. Performance
   8.5. Testability, Usability, Extensibility, Security
   8.6. Long-term
   8.7. Authentication
   8.8. Containerization
   8.9. Portability (Infrastructure as Code)

### 17.2 Strategy for NFR

1. Non-functional req
   1. Availability (LB, ASG, Micro)
   2. Scalability (ASG, Cache, CDN, Async, Micro)
   3. Consistency (ACID, Eventual Consistency)
   4. Latency (Cache, CDN, Edge)
   5. Reliability (Redundancy, Backup, Replication, Failover)
   6. Security (Authentication, Authorization, Encryption, Firewall, VPC, Security Group)

### 17.3 API Gateway

API Gateway: a vital API management tool that acts as the intermediary between clients and a collection of backend services. It provides a single entry point into a system, abstracting and encapsulating the internal architecture. offers functionalities like authentication, monitoring, load balancing, caching, throttling, and logging.

- Authentication and Authorization
- Request and Response Transformation
- Rate Limiting and Throttling
- Caching
- Monitoring and Logging
- Scalability and Load Balancing

Why the API Gateway in front of ELB is often the preferred architecture:

1. API Management: The API Gateway is purpose-built for API management. It offers features like request/response transformation, authentication, authorization, rate limiting, caching, monitoring, and documentation that are crucial for efficiently exposing and managing APIs.
2. Abstraction Layer: The API Gateway acts as an abstraction layer between clients and backend services. This abstraction allows you to evolve your backend services without affecting the API interface exposed to clients.
3. Fine-Grained Control: API Gateway provides fine-grained control over how API requests are handled, authenticated, authorized, and routed to backend resources.
4. Protocol Translation: API Gateway supports multiple protocols and allows you to translate protocols if needed, while ELB primarily deals with network-level load balancing.
5. Serverless Integration: API Gateway seamlessly integrates with AWS Lambda for serverless computing, allowing you to build APIs that directly invoke Lambda functions.
6. Security and Access Control: API Gateway offers extensive security features for API endpoints, including IAM roles, custom authorizers, and OAuth integration, enhancing the overall security posture.
7. Multiple Backend Resources: API Gateway allows integration with various backend resources beyond just ELB, such as Lambda, HTTP endpoints, and AWS services.

### 17.4 Common Single Points of Failure (SPOFs)

- Load Balancer: If a load balancer is the only entry point to a service and it fails, users can't access the service.
- Authentication Services: A central authentication service that fails can prevent users from accessing multiple systems.
- Database Server: A single database server can become a bottleneck or single point of failure if it experiences downtime or data corruption.
- External Services or APIs: Depending on a single external service or API can cause failures if that service experiences issues.

- Hardware Failure: If a critical hardware component, such as a server or storage device, fails, it can disrupt the entire system.
- Network Dependency: Relying on a single network connection or router can result in connectivity issues if it fails.

### 17.5 Common Bottlenecks

- Database Performance: Inefficient database queries, lack of indexing, or high database contention can lead to slow responses.
- Sequential Processing: When tasks must be executed sequentially, it can create a bottleneck and slow down the overall process.
- Synchronization and Locking: Excessive locking or synchronization can lead to contention and reduce performance in multithreaded applications.

- Contention for Resources: Multiple components competing for the same resources (e.g., CPU, memory) can cause contention and slowdowns.
- Inefficient Algorithms: Poorly optimized algorithms can lead to excessive processing times and inefficient resource usage.

- CPU Utilization: High CPU usage can slow down processing and response times for applications.
- Memory Constraints: Insufficient memory can lead to performance degradation and crashes due to excessive swapping.
- Disk I/O: Slow disk I/O can cause delays in reading and writing data, affecting application performance.
- Network Congestion: Heavy network traffic or limited bandwidth can result in delays and data transfer issues.

### 17.6 Mitigation SPOFs and addressing bottlenecks involves

- redundancy
- capacity planning
- load balancing
- efficient resource allocation
- performance optimization

A well-designed system considers these factors to ensure reliability, availability, and optimal performance.

### 17.7 Suggested Prioritization (for a 45-min interview)

- Intro + Functional Requirements → 5m
- Non-functional Requirements → 3m
- Estimation / Scale Analysis → 5m
- High-level Design + Data Flow → 8–10m
- Deep Dive on 1–2 Key Areas → 12–15m
- Trade-offs + Bottlenecks + Failures → 5–7m
- Wrap-up (Evolution/Optimization) → 2–3m

- APIs, schema, and “extra” optimizations: only if time permits.

## 18 Terms

### **API Gateway**

is a **single entry point** for all client requests in a system with **multiple backend services (microservices)**.

#### Why it’s useful:

- Without a gateway:

  - Client must know each service’s URL.
  - Client makes multiple requests (to service A, service B, etc.).
  - Harder to manage authentication, rate limiting, logging across all services.

- With an API Gateway:

  - Client sends **one request to the gateway**.
  - The gateway routes the request to the right microservice.
  - It can also **aggregate responses** from multiple services and return a single result.

#### Common Features of API Gateway:

- **Routing** → Send request to correct service.
- **Aggregation** → Combine responses from multiple services.
- **Security** → Centralized authentication, authorization, rate limiting.
- **Monitoring** → Collect logs/metrics for all requests.
- **Protocol translation** → e.g., client uses REST, backend uses gRPC.

#### Examples:

- AWS API Gateway
- Kong, NGINX, Envoy
- Apigee

---

👉 In **System Design Interviews**, mention API Gateway when:

- You have **multiple microservices**.
- You want to **hide complexity from clients**.
- You need **cross-cutting features** (auth, rate limiting, logging) in one place.

---
comparing without API Gateway vs with API Gateway

- Without API Gateway → the client must directly call each service.
- With API Gateway → the client calls only the gateway, which routes the requests to the right services.

This reduces client complexity, centralizes cross-cutting concerns (auth, logging, caching, rate limiting), and improves maintainability.

Great 👍 Here’s a concise **Pros & Cons of API Gateway** for your notes:

---

#### ✅ Pros of API Gateway

- **Single entry point** → client only needs to know the gateway, not all internal services.
- **Simplifies client code** → no need to manage multiple endpoints.
- **Centralized cross-cutting concerns** → authentication, authorization, logging, monitoring, caching, rate limiting, retries.
- **Protocol translation** → e.g., client uses REST/HTTP, gateway talks gRPC, SOAP, WebSocket internally.
- **Security** → hide internal service details, reduce attack surface.
- **Versioning & routing** → can support multiple versions of APIs, route traffic to new services during migration.

---

#### ❌ Cons of API Gateway

- **Single point of failure** (needs redundancy + load balancing).
- **Added latency** → extra network hop for every request.
- **Operational complexity** → gateway itself must be maintained, scaled, monitored.
- **Potential bottleneck** if not properly designed for high throughput.
- **Coupling risk** → too much logic in gateway can make it a “monolith in disguise.”

---

👉 **Rule of Thumb**: Use an API Gateway when you have **multiple microservices** and need **centralized control & simplicity for clients**. For a small system with just a few services, it may add unnecessary complexity.

---

#### **When do you need a Load Balancer with an API Gateway?**

1. **API Gateway itself needs to scale**

   - If you only run **one instance** of the API Gateway, it becomes a single point of failure.
   - To handle **high traffic**, you run multiple instances of the gateway.
   - A **Load Balancer (LB)** sits in front of them to distribute client requests evenly.

2. **Microservices behind the Gateway also need scaling**

   - Each microservice may run many instances.
   - The API Gateway usually does **service discovery** + **internal load balancing**, but sometimes you add an internal load balancer in front of service clusters.

---

#### **Connection Setup (Typical Flow)**

```
Client 
   ↓
[Load Balancer]  (distributes traffic across multiple API Gateway instances)
   ↓
[API Gateway Cluster]  (auth, routing, rate limiting, logging, etc.)
   ↓
[Internal Load Balancer / Service Discovery] 
   ↓
[Microservice Instances]  (e.g. User Service, Order Service, Payment Service)
```

---

#### **Key Notes for Interviews**

- **External LB** → balances traffic across API Gateway nodes.
- **API Gateway** → central entry point, routes to services.
- **Internal LB or Service Discovery** → balances requests among service replicas.
- In cloud setups (AWS/GCP/Azure), the **cloud provider’s LB** (e.g., AWS ELB/ALB) often handles the LB in front of API Gateways.

---

👉 So the **API Gateway doesn’t replace a Load Balancer**; instead, they complement each other:

- **LB = distribute traffic**
- **Gateway = manage + route traffic**

---
Perfect 👍 Let’s use **AWS** as a concrete real-world example (since it’s widely used and interviewers love it).

---

### **Example: AWS Setup with API Gateway + Load Balancer**

#### **Scenario**

You’re building an **e-commerce platform** with multiple microservices:

* **User Service**
* **Order Service**
* **Payment Service**

Each service runs in **ECS/EKS (containers)** or EC2 instances.

---

#### **Architecture Flow**

```
Client (mobile/web app)
   ↓
[Amazon CloudFront]  (CDN, optional but common for caching & edge delivery)
   ↓
[Elastic Load Balancer (ALB/NLB)]
   ↓
[API Gateway Cluster]  (AuthN/AuthZ, rate limiting, request validation, routing)
   ↓
Service Discovery (e.g., AWS Cloud Map) OR Internal Load Balancer
   ↓
[Microservices running on ECS/EKS]
   ↓
Databases / Caches / Object Storage
```

---

#### **Why Both?**

1. **Elastic Load Balancer (ALB)**

   - Distributes incoming traffic across **multiple API Gateway nodes**.
   - Ensures **high availability** — if one API Gateway fails, traffic goes to others.

2. **API Gateway**

   - Acts as the **entry point** for all APIs.
   - Handles **authentication** (JWT, OAuth, API keys), **rate limiting**, **logging**, and **routing**.
   * Example: `/users/*` → User Service, `/orders/*` → Order Service.

3. **Internal Load Balancers (optional)**

   - Each microservice (e.g., User Service) may scale to many instances.
   - API Gateway either calls them via:

     - **Service discovery** (Cloud Map / Kubernetes service)
     - or **another load balancer** in front of the service cluster.

---

#### **In an Interview, You Can Say:**

> “In a production-grade system, I’d typically place an external load balancer in front of API Gateways to handle traffic distribution and failover. The API Gateway then manages routing, authentication, and request transformation. For scaling microservices, the gateway either integrates with service discovery (like Kubernetes) or uses internal load balancers to distribute traffic among service replicas. For example, in AWS, I might use an Application Load Balancer in front of multiple API Gateway instances, and inside, the gateway routes requests to ECS services with auto-scaling enabled.”

---

Would you like me to **sketch this architecture into a diagram** (ASCII or structured) so you can memorize the flow more visually?

Good question 👍

The short answer is: **API Gateway can sometimes replace a web server, but not always**. Let’s break it down:

---

#### **1. Web Server / Reverse Proxy (Nginx, Envoy, HAProxy)**

- Handles **static content** (HTML, CSS, JS, images).
- Acts as a **reverse proxy** to backend services.
- Provides **basic load balancing**, TLS termination, and sometimes caching.
- Can support **WebSockets** for real-time connections.

👉 If your system needs to serve static assets or handle custom proxy logic, you **still need a web server**.

---

#### **2. WebSockets for Real-Time**

- Used for **bi-directional communication** (chat, gaming, live dashboards).
- Web servers like **Nginx** or specialized infra (e.g., AWS AppSync, Socket.IO servers) usually handle this.
- Many **API Gateways (including AWS API Gateway)** do support WebSockets now, but with **limitations** (scaling, cost, advanced pub-sub).

---

#### **3. API Gateway (if multiple services)**

- Designed as the **entry point for microservices**.
- Provides **routing**, **authentication**, **rate limiting**, and **observability**.
- Not great at serving **static content** or directly managing **long-lived WebSocket connections** (though some gateways do support WebSockets).
- Typically integrates with **load balancers** or service discovery to talk to backends.

---

#### ✅ So, can API Gateway replace Web Server + WebSocket?

- **If you only need API routing (REST/GraphQL/gRPC)** → Yes, API Gateway can replace a reverse proxy.
- **If you need static file serving** → Keep a web server (or use CDN like CloudFront).
- **If you need WebSockets at scale** → Better to use specialized infra (Nginx, Envoy, or AWS AppSync/Kafka pub-sub), not API Gateway alone.

---

#### 🔑 In your note, I’d refine it like this:

**Web Tier**

- **Web server / reverse proxy** (e.g., Nginx, Envoy) → static assets, TLS termination, reverse proxy.
- **WebSockets** for real-time systems (chat, gaming, dashboards).
- **API Gateway** if multiple backend services (REST/GraphQL/gRPC), mainly for routing, auth, rate limiting.

---

👉 This way, it’s clear API Gateway **complements** web servers, not always replaces them.

### Single Point of Failure (SPOF) vs Bottleneck
Great question 👍 Bottlenecks and Single Points of Failure (SPOF) are **related but different concepts** in system design.

---

#### 🔹 **Single Point of Failure (SPOF)**

* **Definition:** A component that, if it fails, the entire system (or a critical function) goes down.
* **Key idea:** It threatens **availability and reliability**.
* **Examples:**

  * Only one database server (if it crashes, no reads/writes can happen).
  * A single load balancer without redundancy.
  * A single power supply for the whole data center.

---

#### 🔹 **Bottleneck**

* **Definition:** A component that **limits the performance** (throughput or latency) of the entire system.
* **Key idea:** It threatens **scalability and performance**.
* **Examples:**

  * A database that can’t handle more than 1,000 writes/sec, while the system needs 10,000.
  * A single-threaded service in a distributed system.
  * A network link capped at 100 Mbps while clients demand 1 Gbps.

---

#### 🔹 **Key Differences**

| Aspect           | Single Point of Failure (SPOF)         | Bottleneck                                          |
| ---------------- | -------------------------------------- | --------------------------------------------------- |
| **Focus**        | Reliability / Availability             | Performance / Scalability                           |
| **Failure Mode** | If it goes down → system/service stops | If it slows down → system throughput is limited     |
| **Solution**     | Redundancy, failover, replication      | Scaling out/in, partitioning, caching, optimization |
| **Analogy**      | One weak link in a chain               | Narrowest pipe in a water system                    |

---

✅ **In interviews:** You usually want to check for **both**.

* SPOFs → “Will my system stay up if X fails?”
* Bottlenecks → “Will my system keep up if usage grows?”

---
Great question 👌 — and it actually depends a little on the **interviewer’s focus** and the **system you’re designing**. But generally:

---

#### 🎯 System Design Interview Priority

1. **First: SPOFs (availability & reliability)**

   * If your system has a **single point of failure**, it doesn’t matter how fast it is — it can go down entirely.
   * Interviewers usually expect you to show awareness of fault tolerance early, e.g.

     * *“Our DB is a SPOF; let’s add replication.”*
     * *“We need multiple load balancers in active-active.”*

2. **Second: Bottlenecks (performance & scalability)**

   * Once you’ve made the system resilient, you shift to **throughput and latency optimization**.
   * Example:

     * *“DB reads are a bottleneck; let’s introduce caching or read replicas.”*
     * *“Uploads are slow; let’s shard storage by user ID.”*

---

#### 🔑 Rule of Thumb for Interviews

* **Reliability first, performance second.**
* A good way to phrase it in interviews:

  > “Let’s first ensure there’s no single point of failure so the system is resilient, then we can address performance bottlenecks as traffic grows.”

