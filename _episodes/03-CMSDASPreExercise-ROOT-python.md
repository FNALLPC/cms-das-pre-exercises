---
title: "CMSDAS Pre-Exercise 3: ROOT and python basics"
teaching: 0
exercises: 60
questions:
- "How do I set up ROOT and python on cmslpc?"
- "How do I inspect a NanoAOD file?"
- "How do I make a quick plot with pyROOT?"
objectives:
- "Learn how to use ROOT and python"
- "Use ROOT and python to inspect a CMS NanoAOD file"
keypoints:
- "ROOT and python are two key software tools in HEP."
- "Many CMS analyses use the NanoAOD format, which are simple ROOT ntuples that can be analyzed with standalone ROOT or pyROOT."
- "There are numerous ways to use ROOT, including the built-in C++ interpreter (Cling), pyROOT, Jupyter notebooks, compiled C++, and more."
---

{% include submit.md episode=3 %}

## Python and ROOT
Python and ROOT are two of the most important software tools in HEP. Before starting:

- **Python:** if you've never used it, work through the [Software Carpentry python lesson](https://swcarpentry.github.io/python-novice-inflammation/). If you know the basics, carry on; you'll learn by doing.
- **ROOT:** work through the [ROOT student course](https://github.com/root-project/student-course) up to at least [02-tfile-read-write-ttree](https://github.com/root-project/student-course/blob/main/course/notebooks/core/02-tfile-read-write-ttree.ipynb). The easiest way is the [SWAN button](https://cern.ch/swanserver/cgi-bin/go?projurl=https://github.com/root-project/student-course.git), which runs the notebooks in your browser on CERN's analysis service.

## Inspect a NanoAOD file with ROOT
Now let's look at real CMS data on cmslpc. Log in as in [Episode 2]({{ page.root }}{% link _episodes/02-CMSDASPreExercise-CMSLPC.md %}#logging-in).

A fresh cmslpc login has no ROOT and an old python. The [LCG releases](https://lcgdocs.web.cern.ch/lcgdocs/lcgreleases/introduction/) provide both; run this once per login:

<!-- TODO(organizers): check this LCG release is still current for the school year. -->
```shell
source /cvmfs/sft.cern.ch/lcg/views/LCG_106a/x86_64-el9-gcc14-opt/setup.sh
```
{: .source}

Open the NanoAOD file you copied in Episode 2 with ROOT's C++ interpreter (`-l` skips the slow splash screen; type `.q` to quit):

```shell
cd ~/nobackup/cmsdas
root -l DYJetsToLL_M50_NANOAOD.root
```
{: .source}

At the ROOT prompt, list the file's contents:

```shell
root [1] _file0->ls()
TFile**		DYJetsToLL_M50_NANOAOD.root
 TFile*		DYJetsToLL_M50_NANOAOD.root
  KEY: TTree	Events;1	Events
```
{: .output}

The file contains one TTree, `Events`. Count its entries:

```shell
root [2] Events->GetEntries()
(long long) 10000
```
{: .output}

`Events->Print()` lists every branch, but NanoAOD has a branch for every CMS trigger, so the list is very long (over 1600 branches). Filter it instead, for example to muon branches only:

```shell
root [3] Events->Print("Muon*")
...
*Br    0 :Muon_dxy  : Float_t dxy (with sign) wrt first PV, in cm            *
*Br    1 :Muon_dxyErr : Float_t dxy uncertainty, in cm                       *
...
```
{: .output}

> ## Question 3.1
> `TTree::GetEntries(const char *selection)` returns the number of events passing a selection (written in C++). Count the events with at least two reconstructed muons:
>
> ```shell
> root [4] Events->GetEntries("nMuon >= 2")
> ```
>
> Enter the number in the answer form.
{: .challenge}

## Plotting with pyROOT
pyROOT lets you use ROOT from python with almost the same commands as in C++.
On cmslpc, with the LCG setup above, start `python3` (`ctrl-d` or `exit()` to quit) and reopen the file:

```python
import ROOT
f = ROOT.TFile("DYJetsToLL_M50_NANOAOD.root", "READ")
f.ls()
```
{: .source}

`TTree::Draw(varexp, selection)` is the fastest way to plot from a TTree: `varexp` is what to plot (a branch or an expression) and `selection` filters the events.
Let's plot the mass of the generator-level Z bosons, i.e. the "truth" particles from the event generator, before detector simulation.
`GenPart_mass` holds the mass of each generated particle, and `GenPart_pdgId` its [PDG ID](https://pdg.lbl.gov/2023/mcdata/mc_particle_id_contents.html) (23 for a Z boson):

```python
events = f.Get("Events")
c = ROOT.TCanvas()
events.Draw("GenPart_mass", "GenPart_pdgId==23")
c.Draw()
```
{: .source}

A plot should appear with a mean close to the Z mass, 91.1876 GeV.
No window? Check that you have an X server on your computer and logged in with `ssh -Y` (see the [cmslpc instructions](https://uscms.org/uscms_at_work/computing/getstarted/uaf.shtml)).

> ## Question 3.2: Z mass plot
> The plot has a "stat box" with basic information about the histogram. Enter the mean of the distribution in the answer form.
{: .challenge}

{% include links.md %}
