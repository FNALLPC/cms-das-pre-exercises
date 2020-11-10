---
title: "CMS Data Analysis School Pre-Exercises - Second Set"
teaching: 0
exercises: 60
questions:
- "How to slim a MiniAOD file?"
- "How to know the size of a MiniAOD file?"
- "How to use FWLite to analyze data and MC?"
objectives:
- "Learn how to reduce the size of a MiniAOD by only keeping variables of interest."
- "Learn how to determine the size of a MiniAOD file using EDM standalone utilities"
- "Learn to use FWLite to perform simple analysis."
keypoints:
- ""
---

# Introduction
Welcome to the second set of CMSDAS pre-exercises. As you know by now, the purpose of the pre-workshop exercises is for prospective workshop attendees to become familiar with the basic software tools required to perform physics analysis at CMS before the workshop begins. Post the answers in the online response form available from the **course web area:**

> ## Indico page
>[CMSDAS pre-exercises indico page](https:/indico.cern.ch/event/966368/)
>
{: .callout} 

The Second Set of exercises begins with `Exercise 7` . We will use Collision data events and simulated events (Monte Carlo (MC)). To comfortably work with these files, we will first make them smaller by selecting only the objects that we are interested in (electrons and muons in our case)

The collision data events are stored in `DoubleMuon.root`. **DoubleMuon** refers here to the fact, that when recording these events, we believed that there are two muons in the event. This is true most of the time, but other objects can fake muons, hence at closer inspection we might find events that actually don't have two muons.

The MC file is called **DYJetsToLL**. You will need to get used to cryptic names like this if you want to survive in the high energy physics environment! The MC file contains Drell Yan events, that decay to two leptons and that might be accompanied by one or several jets. 

`Exercises 8` and `Exercise 9` are using FWLite (**Frame Work Lite**). This is an interactive analysis tool integrated with the CMSSW EDM (Event Data Model) Framework. It allows you to automatically load the shared libraries defining CMSSW data formats and the tools provided, to easily access parts of the event in the EDM format within ROOT interactive sessions. It reads produced ROOT files, has full access to the class methods and there is no need to write full-blown framework modules. Thus having FWLite distribution locally on the desktop one can do CMS analysis outside the full CMSSW framework. In these two exercises, we will analyze the data stored in a MiniAOD sample using FWLite. We will loop over muons and make a Z mass peak.

**We assume that having done the first set of pre-exercises by now, one is comfortable with logging onto** `cmslpc-sl7.fnal.gov` **and setting up the cms environment.**

# Support

## Support email
A large amount of additional information about these exercises is available in the twikis that we reference. Please remember that twikis evolve but aim to provide with the best information at any given time. If problems are encountered please e-mail the -

> ## Email
> **LPC contact** `CMSDASATLPC@fnal.gov` for CMSDAS@LPC{{site.year}}
{: .callout}

## Support chat: Mattermost
There is a dedicated Mattermost team, called CMSDAS@LPC2021, setup to facilitate communication and discussions via live chat (which is also archived). You will need your CERN login credentials (SSO) and you will need to join the private CMSDAS@LPC{{site.year}} team in order to be able to see (or find using the search channels functionality) the channels setup for communications related to the school.

> ## Mattermost
> [CMSDAS@LPC{{site.year}} team](https://mattermost.web.cern.ch/signup_user_complete/?id=dshu1agmwpd4dqxw49ij8wcuec)
{: .callout}

> ## Pre-Exercise Channel
>[Pre Exercise channel](https://mattermost.web.cern.ch/cmsdaslpc2021/channels/preexercises)
{: .callout}

# Obtain a CERN account (in case you don't have one already)
Use the following link for a CMS CERN account: [CMS CERN account](https://account.cern.ch/account/Management/NewAccount.aspx)
A CERN account is needed, for example, to login in to any e-learning web-site, or obtain a file from the afs area. A CERN account will be needed for future exercises.
**Obtaining a CERN account can be time-consuming and requires people at CERN to process applications during business hours. The relevant institutional team leader must start the CERN account request. Try to initiate this process as early as possible.**

#  Obtain a Grid Certificate and CMS VO registration
A Grid Certificate and CMS VO registration will be needed for the Grid Exercises. The registration process can be time-consuming (actions by several people are required), so it is important to start it as soon as possible. There are two main requirements which can be simply summarized: A certificate ensures that you are who you claim to be. A registration in the VO recognizes you (identified by your certificate) as a member of CMS. Use the following link for this: [Get Your Grid Certificate and CMSVO](https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookRunningGrid#GetCert). Both are needed to submit jobs on the Grid. Make sure you follow any additional instructions for US-CMS users.


# Exercise 7 - Slim MiniAOD sample to reduce its size by keeping only Muon and Electron branches
In order to reduce the size of the [MiniAOD](https://twiki.cern.ch/twiki/bin/view/CMS/MiniAOD) we would like to keep only the slimmedMuons and slimmedElectrons objects and drop all others. The config files should now look like [slimMiniAOD_MC_MuEle_cfg.py]({{ page.root }}{% link code/slimMiniAOD_MC_MuEle_cfg.py %}) and [slimMiniAOD_data_MuEle_cfg.py]({{ page.root}}{% link code/slimMiniAOD_data_MuEle_cfg.py %}). To work with this config file and make the slim MiniAOD, execute the following steps in the directory `YOURWORKINGAREA/CMSSW_10_6_18/src`

Cut and paste the script [slimMiniAOD_MC_MuEle_cfg.py]({{ page.root }}{% link code/slimMiniAOD_MC_MuEle_cfg.py %}) and [slimMiniAOD_data_MuEle_cfg.py]({{ page.root}}{% link code/slimMiniAOD_data_MuEle_cfg.py %}) in its entirety and save it with the same name. Open with your favorite editor and take a look at these python files. The number of events has been set to 1000: 

```
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
```
{: .source}

To run over all events in the sample, one can change it to **-1**.

Now run the following command:

```shell
cmsRun slimMiniAOD_MC_MuEle_cfg.py 
```
{: .source}

This produces an output file called `slimMiniAOD_MC_MuEle.root` in your `$CMSSW_BASE/src` area. 

Now run the following command:

```shell
cmsRun slimMiniAOD_data_MuEle_cfg.py
```
{: .source}

This produces an output file called `slimMiniAOD_data_MuEle.root` in your `$CMSSW_BASE/src` area. 

 On opening these two [MiniAODs](https://twiki.cern.ch/twiki/bin/view/CMS/MiniAOD) one observes that only the slimmedMuons and the slimmedElectrons objects are retained as intended.

To find the size of your [MiniAOD](https://twiki.cern.ch/twiki/bin/view/CMS/MiniAOD) execute following Linux command: 		   

```shell
ls -lh slimMiniAOD_MC_MuEle.root
```
{: .source}

and

```shell
ls -lh slimMiniAOD_data_MuEle.root
```
{: .source}

You may also try the following:

To know the size of each branch, use the `edmEventSize` utility as follows (also explained in [First Set of Exercises]({{ page.root }}{% link _episodes/01-CMSDataAnalysisSchoolPreExerciseFirstSet.md %})): 

```shell
 edmEventSize -v slimMiniAOD_MC_MuEle.root
```
{: .source}
and

```shell
 edmEventSize -v slimMiniAOD_data_MuEle.root
```
{: .source}
To see what objects there are, open the ROOT file as follows and browse to the [MiniAOD](https://twiki.cern.ch/twiki/bin/view/CMS/MiniAOD)  samples as you did in [Exercise 6]({{ page.root }}{% link _episodes/01-CMSDataAnalysisSchoolPreExerciseFirstSet.md %}#exercise-6---Get-familiar-with-the-MiniAOD-format): 

Here is how you do it for the output file slimMiniAOD_MC_MuEle.root

```
root -l slimMiniAOD_MC_MuEle.root; 
TBrowser b;
```
{: .source}
OR

```
root -l
TFile *theFile = TFile::Open("slimMiniAOD_MC_MuEle.root");
TBrowser b;
```
{: .source}

To quit ROOT application, execute: 

```
.q
```
{: .source}

>For CMSDAS@LPC{{site.year}}  please submit your answers at the [Google Form second set](https://forms.gle/6zX8sFFkq1jGTY7B7).
{:.caution}

> ## Question 7.1a
> What is the size of the [MiniAOD](https://twiki.cern.ch/twiki/bin/view/CMS/MiniAOD) `slimMiniAOD_MC_MuEle.root`?
{: .challenge}

> ## Question 7.1b
> What is the size of the [MiniAOD](https://twiki.cern.ch/twiki/bin/view/CMS/MiniAOD) `slimMiniAOD_data_MuEle.root`?
{: .challenge}

> ## Question 7.2a
> What is the mean eta of the muons for MC? 
{: .challenge}

> ## Question 7.2b
> What is the mean eta of the muons for data?
{: .challenge}


> ## Question 7.3a
> What is the size of the slimmed output file compared to the original sample?
{: .challenge}

Compare one of your slimmed output files to the original MiniAOD file it came from. To find sizes in EOS, you can use  [`eosls -alh /store/user/filepath/filename.root`](https://uscms.org/uscms_at_work/computing/LPC/usingEOSAtLPC.shtml#listFilesOnEOS) with the appropriate path and filename.

> ## Question 7.3b
> Is the mean eta for muons for MC and data the same as in the original sample in Exercise 6?
{: .challenge}


# Exercise 8 -  Use FWLite on the MiniAOD created in Exercise 7 and make a Z Peak (applying `pt` and `eta` cuts)

FWLite (pronounced "framework-light") is basically a ROOT session with CMS data format libraries loaded. CMS uses ROOT to persistify data objects. CMS data formats are thus "ROOT-aware"; that is, once the shared libraries containing the ROOT-friendly description of CMS data formats are loaded into a ROOT session, these objects can be accessed and used directly from within ROOT like any other ROOT class!

In addition, CMS provides a couple of classes that greatly simplify the access to the collections of CMS data objects. Moreover, these classes (Event and Handle) have the same name as analogous ones in the Full Framework; this mnemonic trick helps in making the code to access CMS collections very similar between the FWLite and the Full Framework. 

In this exercise we will make a `ZPeak` using our data and MC sample. We will use the corresponding slim [MiniAOD](https://twiki.cern.ch/twiki/bin/view/CMS/MiniAOD) created in [Exercise 7]({{ page.root }}{% link _episodes/02-CMSDataAnalysisSchoolPreExerciseSecondSet.md %}#exercise-7---Slim-MiniAOD-sample-to-reduce-its-size-by-keeping-only-Muon-and-Electron-branches). To read more about FWLite, have a look at `Section 3.5` of Chapter `3` of the [WorkBook](https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBook). 

We will first make a `ZPeak`. We will loop over the `slimmedMuons` in the [MiniAOD](https://twiki.cern.ch/twiki/bin/view/CMS/MiniAOD) and get the mass of oppositely charged muons. These are filled in a histogram that is written to an output ROOT file.

First make sure that you have the [MiniAODs](https://twiki.cern.ch/twiki/bin/view/CMS/MiniAOD) created in Exercise 7. They should be called `slimMiniAOD_MC_MuEle.root` and `slimMiniAOD_data_MuEle.root`.

Go to the src area of current CMSSW release

```shell
cd $CMSSW_BASE/src
```
{: .source}

The environment variable CMSSW_BASE will point to the base area of current CMSSW release.

Check out a package from [GitHub](https://github.com/).

Make sure that you get github setup properly as in obtain a GitHub account. It's particularly important to set up ssh keys so that you can check out code without problems: [https://help.github.com/articles/generating-ssh-keys](https://docs.github.com/en/free-pro-team@latest/github/authenticating-to-github/connecting-to-github-with-ssh)

To check out the package, run:

```shell
git cms-addpkg PhysicsTools/FWLite
```
{: .source} 

Then to compile the packages, do

```shell
scram b
cmsenv
```
{:.source}


> ## Note
>You can try `scram b -j 8` to speed up the compiling. Here `-j 8` will compile with 8 cores. When occupying several cores to compile, you will also make the interactive machine slower for others, since you are using more resources. Use with care! 
>
{: .callout}

> ## Note 2
>It is necessary to call cmsenv again after compiling this package because it adds executables in the `$CMSSW_BASE/bin` area.
>
{: .callout}

To make a Z peak, we will use the FWLite executable called `FWLiteHistograms`. The corresponding code should be in `$CMSSW_BASE/src/PhysicsTools/FWLite/bin/FWLiteHistograms.cc`

With this executable we will use the command line options. More about these can be learned from [SWGuideCommandLineParsing](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCommandLineParsing?redirectedfrom=CMS.SWGuideCommandLineParsing).

To make a `ZPeak` from this executable, using the MC [MiniAOD](https://twiki.cern.ch/twiki/bin/view/CMS/MiniAOD), run the following command (which will not work out of the box, see below): 

{% include links.md %}

