---
title: "CMSDAS Pre-Exercise 4: CMSSW basics"
teaching: 0
exercises: 60
questions:
objectives:
- "Setup a CMSSW environment"
- "Use git to download an example EDAnalyzer"
- "Run a CMSSW job on real dimuon data to plot the Z peak"
keypoints:
- "CMSSW is CMS's software framework for data processing."
- "The framework consists of lots of C++ modules, which are configured using python."
- "CMSSW jobs are launched using commands like `cmsRun myCfg.py`"
- "We provide an example EDAnalyzer and cfg.py file for plotting a Z peak directly from a MiniAOD file."
- "Analyzing simple ROOT ntuples like NanoAOD does not need CMSSW!"
---

> ## Questions
> For this lesson, please submit your answers using [CMSDAS@LPC{{ site.year }} Google Form 4][Set4_form].
{: .challenge}

# CMSSW
CMSSW is CMS's software framework for analyzing the data produced by the CMS detector. 
The framework contains a large number of modules (C++), which perform tasks like:
- Loading RAW data (bits from the detector) into nice C++ objects; 
- Reconstructing detector hits, physics objects (tracks, electrons, muons, hadrons, jets, ...); 
- Loading calibrations from databases and applying to physics objects; 
- Interfacing with external generator programs like Pythia and Madgraph_aMC@NLO; 
- Lots and lots of other things. 

With the advent of NanoAOD, a simple ROOT format that does need CMSSW to be analyzed, CMS analysis is increasingly being performed completely outside of CMSSW. Your analysis group might have a framework that uses standalone ROOT, RDataFrame, or Scientific Python (e.g. numpy) instead. CMSSW is needed if your analysis needs additional variables not present in NanoAOD (for example, long-lived particle analysis often need RECO-level objects like tracker or calorimeter hits). You will also probably need to use CMSSW for detector, trigger, and/or POG work. 
{: .callout}

The framework goes hand-in-hand with the "Event Data Model" (EDM), which is how CMS represents events computationally. 
CMS saves events in several formats along the reconstruction chain, including RAW (data straight from detector), RECO (reconstruction performed), AOD (analysis object data=reduced RECO for analysis), MiniAOD (reduced AOD to fit in CMS's disk space in Run 2), and NanoAOD (even further reduced MiniAOD). 
The upstream data formats are typically archived to tape storage, and must be loaded onto disk to be used. 
MiniAOD and NanoAOD are typically available on disk. 
We will learn more about finding data in the next exercise. 

In this exercise, we will learn the basics of CMSSW, from setting up the software environment to running simple jobs. 

# Setting up CMSSW
Login to cmslpc as usual, and run the following commands to create a CMSSW environment. This will create a folder `CMSSW_10_6_30_patch1_cmsdas`, which contains several subfolders. You primarily care about `CMSSW_10_6_30_patch1_cmsdas/src`, which is where you put your code. 

```bash
cd ~/nobackup/cmsdas
source /cvmfs/cms.cern.ch/cmsset_default.sh
scram project -n "CMSSW_10_6_30_patch1_cmsdas" CMSSW_10_6_30_patch1
```
{: .source}

> For convenience, we suggest you edit your `~/.bash_profile` file to call the `cmsset_default.sh` script automatically upon login. Add the whole line to this script. 
{: .callout}

> Note the release number, `10_6_30_patch1`: CMSSW is a massive project that is under continuous development, so we define "releases" that corresponds to a fixed snapshot at some point in time. `CMSSW_10_6_*` is actually a fairly old release, used for NanoAOD production in Run 2. The first number in series (`10`) indicates a major cycle, the second number (`6`) a major release with new features with respect to the preceeding release, and the third number (`30_patch1`) a release with minor updates and bug fixes to the preceeding release.
{: .callout}

Next, execute the following commands to setup the environment in your current shell session:

```shell
cd CMSSW_10_6_30_patch1_cmsdas/src
cmsenv
```
{: .source}

This will provide you with a number of commands and environment variables. For example `$CMSSW_BASE` is a handy variable that points to your CMSSW folder. 

> ## Question 4.1
> The following command prints the location of your CMSSW area. Copy-and-paste the answer into the [Google form 4][Set4_form]. 
> ```shell
> echo $CMSSW_BASE
> ```
> {: .source}
{: .challenge}

> ## Question 4.2
> CMSSW is connected to several external tools, for example the Pythia generator. The following command prints the version of Pythia connected to your current CMSSW release. Fill in the version number in the [Google form 4][Set4_form].
> ```shell
> scram tool info pythia8
> ```
{: .challenge}


# Git
CMS makes extensive use of `git` for code management, and you will use it throughout CMSDAS (CMSSW itself is managed as a git repository, but it's a rather complicated example, so we won't talk about CMSSW+git here). Here, we will simply use git to download some code. First, if you don't already have a github account, go back to the [setup]({{ pages.root }}{% link setup %}) and follow the directions, including setting up the SSH keys. 

Choose your username wisely, it will appear on all your contributions to CMS code! In fact, even if you already have an account, if you have a username like `edgelord1337`, consider either changing it or making a second account.
{: .callout}

Once you have an account, run the following commands to configure git on cmslpc:

```shell
git config --global user.name "[Your name]"
git config --global user.email [Email]
git config --global user.github [Account]
```
{: .source}

Next, run the following commands to "clone" a repository. Make sure not to skip the `cd` line, as the code has to end up in the correct folder structure. 

```shell
cd $CMSSW_BASE/src
git clone git@github.com:FNALLPC/LearnCMSSW MyAnalysis/LearnCMSSW
```
{: .source}

> If the `git clone` fails, it's possible your SSH key was not setup correct. Double check the [setup instructions]({{ pages.root }}{% link setup %}), and head to Mattermost for help. 

This will copy all the code in the repository to `$CMSSW_BASE/src/MyAnalysis/LearnCMSSW`. Feel free to glance through it. 

> ## Question 4.3: git repo info
> When you cloned the repository, you not only downloaded the code, but also setup a local git repository connected to the remote repository. Use the following commands to print out the URL of the remote repository, from which you cloned the code:
> ```shell
> cd $CMSSW_BASE/src/MyAnalysis/LearnCMSSW
> git remote -v
> ```
> Copy and paste the first line into the Google form. 
{: .challenge}

# Running a CMSSW job
Now that we have the source code, we have to compile it. Execute the following to compile the package using [scram](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideScram), CMSSW's build tool:

```shell
cd $CMSSW_BASE/src
scram b
```

`scram b` accept an argument `-j` to use more cores for the compilation. Don't go above `-j4`, as hogging the cores will negatively impact other users on your interactive node. 
{: .callout}

Finally, let's actually run some code. CMSSW jobs are configured through python files. We will use `$CMSSW_BASE/src/MyAnalysis/test/zpeak_cfg.py`, which is a simple configuration file that loads the plugin at `$CMSSW_BASE/src/MyAnalysis/LearnCMSSW/plugins/ZPeakAnalyzer.cc`. The `ZPeakAnalyzer` processes some dimuon events in MiniAOD format and produces some histograms (a bit of an uncommon workflow, as it is typically more efficient to make histograms from NanoAOD or another slimmed-down format). Launch CMSSW with the following:

```shell
cd $CMSSW_BASE/src/MyAnalysis/LearnCMSSW/test
cmsRun zpeak_cfg.py
```
{: .source}

The job will take a minute to run, periodically updating you on the progress. When it's done, you should see a file `ZPeak.root`. Let's open it and plot the Z peak:

```shell
root -l ZPeak.root
[0] TH1D* dimuonMass = (TH1D*)_file0->Get("zpeak_analyzer/dimuonMass")
[1] dimuonMass->Draw()
```

> ## Question 4.4
> Using the stat box drawn along with the histogram, what is the mean dimuon mass? Write your answer in the Google form. 
{: .challenge}

[Set4_form]: https://forms.gle/mSntaw8AAGty2Kmp8