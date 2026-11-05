---
title: "CMSDAS Pre-Exercise 5: CMSSW basics"
teaching: 0
exercises: 60
questions:
- "What is CMSSW, and when do I need it?"
- "How do I set up a CMSSW release?"
- "How do I compile and run a CMSSW job?"
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

{% include submit.md episode=5 %}

## CMSSW
CMSSW is CMS's software framework for processing and analyzing data. It is made of many C++ modules that, for example:
- turn RAW detector data into C++ objects;
- reconstruct hits and physics objects (tracks, electrons, muons, jets, ...);
- load calibrations from databases and apply them;
- run event generators like Pythia and MadGraph5_aMC@NLO.

CMS stores events in a chain of formats, each smaller than the last:
**RAW** (straight from the detector) → **RECO** (reconstructed) → **AOD** → **MiniAOD** → **NanoAOD**.
The early formats are mostly archived on tape; MiniAOD and NanoAOD are usually on disk. You'll learn to find them in the next episode.

> ## Do you need CMSSW?
> NanoAOD is a plain ROOT format that does **not** need CMSSW, and many analyses now run entirely outside it, using ROOT, RDataFrame, or scientific python.
> You do need CMSSW if your analysis needs information missing from NanoAOD (for example, long-lived particle searches often need tracker or calorimeter hits), and for most detector, trigger, and POG work.
{: .callout}

## Setting up CMSSW
CMSSW comes in **releases**, fixed snapshots of the code. A release name such as `CMSSW_13_0_10` gives the major cycle (`13`), a feature release (`0`), and a bug-fix release (`10`).
`CMSSW_13_0_X` was used for 2023 data taking and for [NanoAODv12](https://gitlab.cern.ch/cms-nanoAOD/nanoaod-doc/-/wikis/Releases/NanoAODv12). See the [release schedule](https://twiki.cern.ch/twiki/bin/view/CMS/ReleaseSchedule) for the full list.

> ## Start from a fresh login
> Software environments don't mix: if the LCG setup from the previous episode (or conda, etc.) is active in the same session, CMSSW will break. Log out and back in to cmslpc first.
{: .callout}

Create a CMSSW area in your work folder. This makes a folder `CMSSW_13_0_10_cmsdas`; your code goes in its `src` subfolder.

<!-- TODO(organizers): check whether CMSSW_13_0_10 should be updated for the school year (also used in Episode 6). -->
```shell
cd ~/nobackup/cmsdas
source /cvmfs/cms.cern.ch/cmsset_default.sh
scram project -n "CMSSW_13_0_10_cmsdas" CMSSW_13_0_10
cd CMSSW_13_0_10_cmsdas/src
cmsenv
```
{: .source}

`cmsenv` sets up the release in your current shell; run it again (from inside `src`) every time you log in.
Tip: add the `source /cvmfs/cms.cern.ch/cmsset_default.sh` line to your `~/.bash_profile` so it runs at every login.

`cmsenv` also defines handy variables, such as `$CMSSW_BASE`, which points to your CMSSW folder.

> ## Question 5.1
> Print the location of your CMSSW area, and enter it in the answer form:
> ```shell
> echo $CMSSW_BASE
> ```
> {: .source}
{: .challenge}

> ## Question 5.2
> Each release comes with external tools, such as the Pythia generator. Print the Pythia version in your release and enter the version number in the answer form:
> ```shell
> scram tool info pythia8
> ```
> {: .source}
{: .challenge}

## Getting the example code with git
Configure git on cmslpc as in [Episode 4]({{ page.root }}{% link _episodes/04-CMSDASPreExercise-git.md %}#configure-git), if you haven't already.
Then clone the example analysis. The `cd` matters: CMSSW expects code in `src/<Package>/<SubPackage>`.

```shell
cd $CMSSW_BASE/src
git clone git@github.com:FNALLPC/LearnCMSSW MyAnalysis/LearnCMSSW
```
{: .source}

If the clone fails, your SSH key is probably not set up on GitHub; see the [setup instructions][lesson-setup].

> ## Question 5.3: git repo info
> Cloning also set up a local git repository connected to the one on GitHub. Print the address of that remote repository:
> ```shell
> cd $CMSSW_BASE/src/MyAnalysis/LearnCMSSW
> git remote -v
> ```
> {: .source}
> Enter the first line of the output in the answer form.
{: .challenge}

## Running a CMSSW job
Compile the code with [scram](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideScram), CMSSW's build tool. (`scram b -j4` uses 4 cores; don't go higher on the shared interactive nodes.)

```shell
cd $CMSSW_BASE/src
scram b
```
{: .source}

CMSSW jobs are configured with python files and run with `cmsRun`.
The configuration `MyAnalysis/LearnCMSSW/test/zpeak_cfg.py` runs the `ZPeakAnalyzer` module (`MyAnalysis/LearnCMSSW/plugins/ZPeakAnalyzer.cc`), which reads dimuon events in MiniAOD format and fills some histograms:

```shell
cd $CMSSW_BASE/src/MyAnalysis/LearnCMSSW/test
cmsRun zpeak_cfg.py
```
{: .source}

The job takes about a minute and writes `ZPeak.root`. Open it and plot the Z peak:

```shell
root -l ZPeak.root
root [0] TH1D* dimuonMass = (TH1D*)_file0->Get("zpeak_analyzer/dimuonMass")
root [1] dimuonMass->Draw()
```
{: .source}

> ## Question 5.4
> What is the mean dimuon mass shown in the histogram's stat box? Enter it in the answer form.
{: .challenge}

{% include links.md %}
