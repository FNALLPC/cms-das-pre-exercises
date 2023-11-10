---
title: "CMSDAS Pre-Exercise 3: ROOT and python basics"
teaching: 0
exercises: 60
questions:
objectives:
- "Learn how to use ROOT and python"
- "Use ROOT and python to inspect a CMS NanoAOD file"
keypoints:
- "ROOT and python are two key software tools in HEP."
- "Many CMS analyses use the NanoAOD format, which are simple ROOT ntuples that can be analyzed with standalone ROOT or pyROOT."
- "There are numerous ways to use ROOT, including the build-in command line interface (based on CINT, a C++ interpreter), pyROOT, Jupyter notebooks, compiled C++, and more."
---

> ## Questions
For this lesson, please submit your answers for the [CMSDAS@LPC{{ site.year }} Google Form 3][Set3_form].
{: .challenge}

# Python and ROOT

Python and ROOT are two of the most important software tools in HEP. If you have never used python before, we highly recommend you go through a tutorial, for example the [HSF python lesson](https://swcarpentry.github.io/python-novice-inflammation/). If you are comfortable with basic python, feel free to proceed, as you will learn by doing in the following exercises. 

For ROOT, please follow the lesson on the HEP Software Foundation website for [ROOT](https://swcarpentry.github.io/python-novice-inflammation/), up through at least the fifth lesson, "05-tfile-read-write-ttrees.ipynb" (of course, you can keep going and learn about RDataFrames, but we won't use them here). We recommend you click the "SWAN" button, which opens a session in CERN's "Service for Web-based ANalysis." From the service, you can open and run code through Jupyter notebooks, all inside the web browser.

# Inspect a NanoAOD file with ROOT
Once you're comfortable with python and ROOT, let's go back to cmslpc and look at some real CMS data. 
Login to the cluster again:

```shell
kinit -f <YourUsername>@FNAL.GOV
ssh -Y <YourUsername>@cmslpc-sl7.fnal.gov
```
 {: .source}

By default, your shell environment will not have ROOT, and will have some very old version of python. 
A quick way to setup ROOT is to use the [LCG (LHC Computing Grid) releases](https://lcgdocs.web.cern.ch/lcgdocs/lcgreleases/introduction/). 
All you have to do is execute the following script (once per login):

```shell
source /cvmfs/sft.cern.ch/lcg/views/LCG_104/x86_64-centos7-gcc12-opt/setup.sh
```
 {: .source}

 First, let's inspect a ROOT file using ROOT's built-in C++ interpreter, CINT. 
 Run the following to launch ROOT and simultaneously open a file (the same file we copied from EOS in the previous exercise).

 ```shell
cd ~/nobackup/cmsdas
root -l DYJetsToLL_M50.root
# Note: the -l option stops ROOT from displaying its logo image, which is very slow over SSH
```
 {: .source}

CINT is a quick way to inspect files (to exit CINT, just type `.q`). First, let's see what's in the file:

```shell
root [1] _file0->ls()
TFile**		DYJetsToLL_M50.root	
 TFile*		DYJetsToLL_M50.root	
  KEY: TTree	Events;1	Events
```
{: .output}

The file contains just one interesting object, a TTree named Events. Next, let's check the basic contents of Events. For the number of events in the TTree:
```shell
root [4] Events->GetEntries()
(long long) 10000
```
{: .output}

For the branches in Events, try:
```shell
root [6] Events->Print()
******************************************************************************
*Tree    :Events    : Events                                                 *
*Entries :    10000 : Total =        65055196 bytes  File  Size =   19389904 *
*        :          : Tree compression factor =   3.33                       *
******************************************************************************
*Br    0 :run       : run/i                                                  *
*Entries :    10000 : Total  Size=      40621 bytes  File Size  =        410 *
*Baskets :        2 : Basket Size=      29696 bytes  Compression=  97.91     *
*............................................................................*
*Br    1 :luminosityBlock : luminosityBlock/i                                *
*Entries :    10000 : Total  Size=      40693 bytes  File Size  =        493 *
*Baskets :        2 : Basket Size=      29696 bytes  Compression=  81.48     *
*............................................................................*
*Br    2 :event     : event/l                                                *
*Entries :    10000 : Total  Size=      80641 bytes  File Size  =      20690 *
*Baskets :        2 : Basket Size=      58880 bytes  Compression=   3.87     *
```
{: .output}

This prints out a super long list of branches, because NanoAOD assigns a branch for every trigger in CMS. You can filter to looks at, e.g., only muon branches:

```shell
root [8] Events->Print("Muon*")
******************************************************************************
*Tree    :Events    : Events                                                 *
*Entries :    10000 : Total =        65055196 bytes  File  Size =   19389904 *
*        :          : Tree compression factor =   3.33                       *
******************************************************************************
*Br    0 :Muon_dxy  : Float_t dxy (with sign) wrt first PV, in cm            *
*Entries :    10000 : Total  Size=      67214 bytes  File Size  =      29269 *
*Baskets :        4 : Basket Size=      32000 bytes  Compression=   2.28     *
*............................................................................*
*Br    1 :Muon_dxyErr : Float_t dxy uncertainty, in cm                       *
*Entries :    10000 : Total  Size=      67222 bytes  File Size  =      21835 *
*Baskets :        4 : Basket Size=      32000 bytes  Compression=   3.05     *
...
```
{: .output}


## Question 3.1
The method ``Long64_t TTree:GetEntries (const char *selection)`` accepts a selection string, and returns the number of events passing the selection criteria (note: written in C++). Use this method to get the number of events with two reconstructed muons:

```shell
root [0] Events->GetEntries("nMuons >= 2")
```

Write the number of events with at least 2 muons in the Google form. 
{: .challenge}

# Plotting with pyROOT
You can also use ROOT in python, almost identically to CINT except with python instead of C++. 
(This is possible because of pyROOT, a wrapper around ROOT that creates a nearly 1-to-1 map of all the C++ classes to python classes.)
Make sure you're logged into cmslpc, and that you have called the LCG setup script in the session. 
Then, let's reopen the NanoAOD file in python (note: enter ctrl-d to quit):

```shell
cmslpc169:~/nobackup/DAS/2024/preexercises --> python
Python 3.9.12 (main, Oct 19 2022, 15:11:58) 
[GCC 12.1.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import ROOT
f = ROOT.TFile("DYJetsToLL_M50.root", "READ")
>>> f.ls()
```
{: .source}

You should see the same contents of the file as before. 

`Long64_t TTree::Draw(const char * varexp, const char * selection, ...)` is a fast way to make a plot from a TTree. 
The first argument, `varexp`, is what you want to plot (accepts single branches as well as expressions; the string is compiled on the fly by CINT). 
The second argument, `selection`, allows you to filter events before plotting. 
Let's use this function to plot the generator-level Z boson mass distribution, i.e., the truth particles generated by Madgraph (versus the reconstructed particles after the CMS detector simulation has been run). 
The branch `GenPart_mass` contains the mass of all generator-level particles. 
The branch `GenPart_pdgId` contains the so-called [PDG ID](https://pdg.lbl.gov/2023/mcdata/mc_particle_id_contents.html) of the generator-level particles; Z bosons are assigned a PDG ID of 23. 
```python
>>> events = f.Get("Events")
>>> events.Draw("GenPart_mass", "GenPart_pdgId==23")
```
{: .source}

A plot of the Z boson mass should appear, with a mean value close to the Z boson mass of 91.1876 GeV. (If no plot appears, something is probably wrong with the X window system that displays graphical windows over SSH. Following [the cmslpc instructions](https://uscms.org/uscms_at_work/computing/getstarted/uaf.shtml), make sure you have an X windows program installed on your computer, and that you logged in using `ssh -Y`; ask Mattermost for more help.)


## Question 3.2: Z mass plot
The plot includes a "stat box" with basic information about the plotted histogram. 
Please fill in the mean of the distribution in the Google form. 
{: .challenge}

[Set3_form]: https://forms.gle/KpqmLGGk6aV1thbB8