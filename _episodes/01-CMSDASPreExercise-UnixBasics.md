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

---

{% include submit.md episode=1 %}

All CMSDAS@LPC {{ site.year }} participants should answer the questions in these exercises. Each episode has its own section in the answer form, linked in the box above.

The rest of the pre-exercises take place in Unix. If you have never used it, work through the [HEP Software Foundation training](https://hsf-training.github.io/hsf-training-unix-shell/01-intro.html), up to at least "3. Working With Files and Directories."

> ## Question 1.1
> Check that you have a working Unix shell on **your personal laptop**. Copy-and-paste the following into your shell:
> ~~~shell
> echo "$(whoami) $(date)"
> ~~~
> {:.source}
> This prints your username followed by the current date and time. Enter the output in the answer form.
{: .challenge}

{% include links.md %}
