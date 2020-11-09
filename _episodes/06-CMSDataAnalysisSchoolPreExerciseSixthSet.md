---
title: "CMS Data Analysis School Pre-Exercises - Sixth Set"
teaching: 0
exercises: 30
questions:
- "What is Jupyter?"
- "What is pyROOT?"
objectives:
- "Learn how to use Jupyter and the Vanderbilt JupyterHub."
- "Learn how to interact with the ROOT libraries using pyROOT."
keypoints:
- "pyROOT is an easy to use alternative to using the ROOT libraries in a C++ program."
- "Jupyter notebooks are a great way to perform real-time analysis tasks."
---

# Introduction

This exercise is intended to provide you with basic familiarity with pyROOT provides bindings for all classes within the ROOT libraries and allows for replacing the usual C++ with the often less cumbersome python. The goal is to obtain a general understanding of the syntax required to import and make use of the ROOT libraries within a basic python script. Various examples are provided in order to demonstrate TH1 histogram manipulation including; reading from a .root file, creating, binning, re-binning, scaling, plotting and fitting to a Gaussian.

Many courses have begun to use Jupyter notebooks as a teaching tool, this exercise has been formatted as a notebook to give a preliminary introduction to how they work. This knowledge will be used later in various DAS exercises.

Whether you use python or C++ to complete your analysis is a personal preference. However, with the current lack of documentation on pyROOT, many students stick with C++ in order to ensure their access to coding examples and experts. It is our hope that through providing you with this basic introduction and Github repository of example scripts, which you are encouraged to add to, that we can bring together the existing pyROOT community within CMS and foster its growth.

> ## Warning
> As a prerequisite for this exercise, please make sure that you have correctly followed the instructions for obtaining a [GitHub] account in the [setup instructions]({{ page.root }}{% link setup.md %}).
> 
> It is also helpful to have already completed the "Collaboration on GitHub" section of the [fifth set of exercises]({{ page.root }}{% link _episodes/05-CMSDataAnalysisSchoolPreExerciseFifthSet.md %}).
{: .prereq}

> ## Note
> Please post your answers to the questions in the [online response form](https://forms.gle/iC3RDAZmTnoHkMbL9).
{: .objectives}

# Exercise 19 - Introduction to pyROOT and Jupyter

## Load and execute the exercise on JupyterHub

This exercise is stored completely within Jupyter notebooks. This exercise will use a premade Jupyter service hosted at [Vanderbilt](https://jupyter.accre.vanderbilt.edu/). To begin, visit [https://github.com/FNALLPC/pyROOTforCMSDAS](https://github.com/FNALLPC/pyROOTforCMSDAS) and follow the directions on the first page.

> ## Question 19.1
> What is the mean value of the Gaussian fit of the jet mass spectrum for jets of pt 300-400 GeV?
{: .challenge}

Hopefully this extremely brief introduction has piqued your interest in pyROOT and encouraged you to learn more about this versatile tool.

## Advanced topics

Advanced topics not explored in this exercise, but to be included on the pyROOT for CMSDAS GitHub page in the near future are:
 - reading and writing a TTree
 - using a python analyzer to skim a TTree
 - creating plots in the CMS PubCom format 

Students are encouraged to explore these and other topics on their own and to assist with the CMS effort to document pyROOT by creating your own fork of [pyROOTforCMSDAS](https://github.com/FNALLPC/pyROOTforCMSDAS) and adding to the example scripts available there. 

{% include links.md %}
