---
title: "CMSDAS Pre-Exercise 7: Statistics reading course"
teaching: 0
exercises: 0
questions:
- "Which statistics concepts should I know before CMSDAS?"
- "Where can I learn them, at my own pace?"
objectives:
- "Learn the basics of each topic in the statistics reading course before CMSDAS."
- "Run the interactive examples to build intuition."
keypoints:
- "The reading course covers the statistics used in HEP analyses: probability, uncertainties, Monte Carlo, likelihood fits, hypothesis tests, and confidence intervals."
- "Many sections are executable notebooks you can run in your browser with Binder."
- "Ask questions in the StatisticsReadingCourse Mattermost channel."
---

> ## Optional, but a real head start
> - This episode is *not* required to register for CMSDAS and has no questions to submit, but we strongly encourage everyone to do it.
> - Almost every CMSDAS Long exercise ends in a fit, a significance, or a limit. Students who arrive knowing the basic concepts will have a real advantage, instead of learning the statistics under time pressure during the school.
> - The same concepts are behind every CMS result you will work on after CMSDAS, so the effort pays off well beyond the school.
> - Covering the basics takes steady effort over a few weeks, so **start early**.
{: .callout}

## The course
[Statistical Methods and Data Analysis Techniques](https://mdonega.github.io/hep-datanalysis-jb/preface.html) is an online book of reading material on the basic concepts of statistics.

Why this course?
- **Written by a CMS physicist,** in the language physicists use, and focused on the topics most relevant to HEP analyses.
- **Interactive:** many sections are Jupyter notebooks you can run and modify in your browser via [Binder](https://mybinder.org/), with no installation needed.

> ## Acknowledgement
> The course is written by [Mauro Donegà](https://mdonega.github.io/hep-datanalysis-jb/preface.html) (ETH Zürich), based on the ETH Zürich master's course *Statistical Methods and Analysis Techniques in Experimental Physics*, taught with Christoph Grab and Christian Regenfüs.
> We thank Mauro for allowing CMSDAS to use this material.
{: .testimonial}

## How to use it
Working through the full course at your own pace takes **about 3 weeks**. You don't need all of it before CMSDAS: aim to **learn the basics of each topic** below, and go deeper wherever you are curious or where your analysis will need it.

- Read the book online in order, using the arrows at the bottom of each page, or jump to a topic from the sidebar.
- On notebook pages, click the **rocket icon** (top right) → **Binder** to run the code. Binder takes a minute or two to start, and its sessions are temporary: download the notebook (download icon) if you want to keep your changes.

| Topic | Read | Try it interactively |
|---|---|---|
| Probability | [Introduction](https://mdonega.github.io/hep-datanalysis-jb/introduction.html), [Probability](https://mdonega.github.io/hep-datanalysis-jb/probability.html) | [Conditional probability](https://mdonega.github.io/hep-datanalysis-jb/interactive-nbs/ConditionalProbability.html), [Bayes theorem](https://mdonega.github.io/hep-datanalysis-jb/interactive-nbs/BayesTheorem.html) |
| Distributions | [Probability distributions](https://mdonega.github.io/hep-datanalysis-jb/probabilityDistributions.html) | [Random walk](https://mdonega.github.io/hep-datanalysis-jb/interactive-nbs/randomWalk.html) |
| Uncertainties | [Measurement uncertainties](https://mdonega.github.io/hep-datanalysis-jb/errors.html) | [Error matrix](https://mdonega.github.io/hep-datanalysis-jb/interactive-nbs/ErrorMatrix.html) |
| Monte Carlo | [Monte Carlo methods](https://mdonega.github.io/hep-datanalysis-jb/monteCarlo.html) | [Random numbers with numpy](https://mdonega.github.io/hep-datanalysis-jb/interactive-nbs/randomNumbers.html) |
| Parameter estimation | [Statistical inference](https://mdonega.github.io/hep-datanalysis-jb/inference.html), [Likelihood](https://mdonega.github.io/hep-datanalysis-jb/likelihood.html), [Least squares](https://mdonega.github.io/hep-datanalysis-jb/leastSquares.html) | [ML method: mean of a Gaussian](https://mdonega.github.io/hep-datanalysis-jb/interactive-nbs/MLMethod.html), [From least squares to likelihood](https://mdonega.github.io/hep-datanalysis-jb/interactive-nbs/StraighLineFit_LSM_vs_MLM.html) |
| Hypothesis testing | [Hypothesis testing](https://mdonega.github.io/hep-datanalysis-jb/hypothesisTesting.html) | |
| Confidence intervals and limits | [Confidence intervals](https://mdonega.github.io/hep-datanalysis-jb/confidenceIntervals.html) | [Poisson intervals](https://mdonega.github.io/hep-datanalysis-jb/interactive-nbs/Poisson_CI.html), [Upper limit](https://mdonega.github.io/hep-datanalysis-jb/interactive-nbs/UpperLimit.html) |
| Multivariate analysis | [Multivariate analysis methods](https://mdonega.github.io/hep-datanalysis-jb/mva.html) | |

To check your understanding, try the [exercises](https://mdonega.github.io/hep-datanalysis-jb/exercises.html) at the end of the book.

## Questions and discussion
There is a dedicated Mattermost channel for this course: [StatisticsReadingCourse](https://mattermost.web.cern.ch/cmsdaslpc{{ site.year }}/channels/statisticsreadingcourse).
**Please ask questions there**, however basic: someone else is probably wondering the same thing, and discussing with other students is a great way to learn.
The channel is in the CMSDAS@LPC {{ site.year }} Mattermost team; if the link doesn't open, join the team first (see the [setup instructions][lesson-setup]).

{% include links.md %}
