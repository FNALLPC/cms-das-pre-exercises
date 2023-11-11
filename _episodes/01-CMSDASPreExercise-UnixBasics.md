---
title: "CMSDAS Pre-Exercise 1: Unix basics"
teaching: 25
exercises: 5
questions:
- "How do I get started with Unix?"
- "How do I navigate the filesystem?"
- "How do I manipulate files and folder?"
objectives:
- "Setup a working Unix environment on your laptop."
- "Learn how to use folders and files in Unix."
keypoints:
- "Unix is the primary OS used in HEP, CMS included."
- ""

---

If you have never used Unix before, please follow the lesson on the [HEP Software Foundation website](https://swcarpentry.github.io/shell-novice/03-create.html), through at least "3. Working With Files and Directories." The remainder of the pre-exercises takes place in Unix, so you will need to be familiar with the basics. 

> ## Question 1.1
> All CMSDAS@LPC2024 participants should submit answers to the questions in these exercises. Each lesson has it's own Google form. Head to [Google form 1][Set1_form]. The first question verifies that you have a working Unix environment. Copy-and-paste the following into your shell:
> ~~~shell
> echo "$(whoami) $(date)"
> ~~~
> {:.source}
> This should print your username followed by the current date and time. Copy-and-paste the output into the Google form. 
{: .challenge}

[Set1_form]: https://forms.gle/hK38xSuBXvzYBhJe6



> ## Hint
> You can easily download the needed files by running the following commands:
> ~~~shell
> wget https://fnallpc.github.io/cms-das-pre-exercises/code/FWLiteWithPythonConfig.cc -O $CMSSW_BASE/src/PhysicsTools/FWLite/bin/FWLiteWithPythonConfig.cc
> wget https://fnallpc.github.io/cms-das-pre-exercises/code/parameters.py -O $CMSSW_BASE/src/parameters.py
> ~~~
> {: . source}
{: .challenge}