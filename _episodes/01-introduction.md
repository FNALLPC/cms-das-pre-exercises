---
title: "Introduction"
teaching: 10
exercises: 0
questions:
- "What are containers?"
- "What is Docker?"
- "What is it used for?"
- "What are its components?"
- "How is Docker different on OSX/Windows/Linux?"
objectives:
- "Understand what is a container and how it differs from a virtual machine."
- "Understand the purpose of Docker."
- "Understanding why docker is useful to CMS researchers."
keypoints:
- "Docker provides loosely isolated environments called containers."
- "These containers are lightweight alternatives to virtual machines."
- "You can package and run software in containers."
- "You can run many containers simultaneously on a single host machine."
---

# Containers and Images

Containers are like lightweight virtual machines. They behave as if they were their own complete OS, but actually only contain the components necessary to operate. Instead, containers share the host machine's system kernel, significantly reducing their size. In essence, they run a second OS natively on the host machine with just a thin additional layer, which means they can be faster than traditional virtual machines. These container only take up as much memory as necessary, which allows many of them to be run simultaneously and they can be spun up quite rapidly.

<img src="../fig/DockerVM.png" alt="DockerVM" style="width:800px"> 

{% include links.md %}
