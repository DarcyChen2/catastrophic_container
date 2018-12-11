# Catastrophic container

One Paragraph of project description goes here

# features

    Misc Features:
        1. good user experience
    Process/Resource Management Features
        1. Container moves into a new namespace (mount, user, PID, net)
        2. init process that cleans up orphans
    Networking Features
        1. assign an IP to the container
        2. limit number of processes
    Filesystem Features
        1. full read/write to the container
        2. full write access to the container without polluting the real filesystem
        3. container launches in a new root partition
        4. /dev, /proc, /sys, have been remounted and are reporting information from the        current namespace
    User Features
        1. have a user in the container that is not root
        2. have a user in the container that has sudo privileges
        

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.


## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

