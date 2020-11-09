---
title: "CMS Data Analysis School Pre-Exercises - Fourth Set"
teaching: 0
exercises: 60
questions:
- ""
objectives:
- ""
keypoints:
- ""
---

# Introduction

In this set of exercises, we will analyze the [MiniAOD][miniaod] file that was made in the [third set of exercise]({{ page.root }}{% link _episodes/03-CMSDataAnalysisSchoolPreExerciseThirdSet.md %}). You must have this skimmed [MiniAOD][miniaod] stored locally (at T3_US_FNALLPC) in order to access them. We will use several different workflows for analyzing the [MiniAOD][miniaod], namely an EDAnalyzer, a FWLite executable, a FWLite Macro, and a FWLite PyROOT script. We will basically re-make the Z peak and few other histograms and store them in an output root file. In the exercise in the end we will try to fit with a Gaussian, Breit-Wigner function, etc.

> ## Warning
> To perform this set of exercises, an [LPC](https://twiki.cern.ch/twiki/bin/view/CMS/LPC) account, Grid Certificate, and CMS VO membership are required. You should already have these things, but if not, follow these instructions from the [setup instructions]({{ page.root }}{% link setup.md %}).
{: .prereq}

> ## Note
> Please post your answers to the questions in the [online response form](https://forms.gle/kHZ71u12kDfrTd2f8.
{: .objectives}

# Exercise 15 - Analyzing MiniAOD with an EDAnalyzer

In this exercise we will analyze the skimmed [MiniAODs][miniaod] created in the [third set of exercises]({{ page.root }}{% link _episodes/03-CMSDataAnalysisSchoolPreExerciseThirdSet.md %}) using an `EDAnalyzer`. In these skimmed [MiniAODs][miniaod], if you recall, we saved only the muons and electrons. So do not look for jets, photons, or other objects as they were simply not saved. We will use a python `config` file and an `EDAnalyzer` ( a `.cc` file) to make a Z mass peak. You can find an example list of files below, but please first try using the files you created.

> ## Example file list
> ```
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_1.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_10.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_11.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_12.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_13.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_14.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_15.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_16.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_17.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_18.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_19.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_2.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_20.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_21.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_22.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_23.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_24.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_25.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_26.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_27.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_28.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_29.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_3.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_30.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_31.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_4.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_5.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_6.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_7.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_8.root
> root://cmseos.fnal.gov//eos/uscms/store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_9.root
> ```
{: .solution}

First we will add the [PhysicsTools](https://twiki.cern.ch/twiki/bin/view/CMS/PhysicsTools)/PatExamples package as follows to `<YOURWORKINGAREA>/CMSSW_10_6_18/src`. As always, feel free to use whatever path you'd like in place of `<YOURWORKINGAREA>`. The `PatExamples` package has lot of examples for a user to try. However, we will add our own code and config file to it and then compile. To add this package, do this:

```shell
cd $CMSSW_BASE/src/
git cms-addpkg PhysicsTools/PatExamples
```
{: .source}

In this package, you will find the python configuration file `$CMSSW_BASE/src/PhysicsTools/PatExamples/test/analyzePatBasics_cfg.py`. You will also see the EDAnalyzer in `$CMSSW_BASE/src/PhysicsTools/PatExamples/plugins/PatBasicAnalyzer.cc`.

Next, create the following two files (copy, paste, and save): [$CMSSW_BASE/src/PhysicsTools/PatExamples/src/MyZPeakAnalyzer.cc]({{ page.root }}{% link code/MyZPeakAnalyzer-CMSSW_10_6_18.cc %}) and [$CMSSW_BASE/src/MyZPeak_cfg.py]({{ page.root }}{% link code/MyZPeak_cfg.py %}).

Then we will compile the code that you just saved by doing:

```shell
cd $CMSSW_BASE/src/
scram b -j 4
```
{: .source}

The compilation should print many lines of text to your terminal. Among those lines you should see a line like the one below. If you can't find a similar line, then the code you just added is not compiled.

```
>> Compiling  <$CMSSW_BASE>/src/PhysicsTools/PatExamples/src/MyZPeakAnalyzer.cc
```
{: .output}

After successful compilation, you must run the config file as follows:

```shell
cmsRun MyZPeak_cfg.py
```
{: .source}

Successful running of the above config file will produce an output file `myZPeakCRAB.root`. The output file myZPeakCRAB.root has several histograms, besides the Z peak, called mumuMass, like muonMult, muonEta, muonPhi, muonPt and similarly for electrons.

> ## Note
> 
> In the case above, the file `MyZPeak_cfg`.py will read from area `root://cmseos.fnal.gov//store/user/cmsdas/2021/pre_exercises/Set4/Input/DoubleMuon/`. You should have a similar location from where you can read your [CRAB][crab] output `ROOT` files. You can edit the `MyZPeak_cfg.py` file to use the [MiniAOD][miniaod] files you made in [Exercise 13]({{ page.root }}{% link _episodes/03-CMSDataAnalysisSchoolPreExerciseThirdSet.md %}#exercise-13---running-on-dataset-with-crab) by replacing the location of the input files to the path of file you generated"
> 
> ```
> 'root://cmseos.fnal.gov//store/user/cmsdas/2021/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_1.root', (at cmslpc) or
> 'file:/afs/cern.ch/work/d/dmoon/public/CMSDAS_Files/Exe4/slimMiniAOD_data_MuEle_1.root', (at lxplus or Bari) or
> 'file:/cmsdas/data/pre_exercises/Exe4/slimMiniAOD_data_MuEle_1.root', (at KNU) or
> 'file:/pnfs/desy.de/cms/tier2/store/user/your_username/DoubleMuon/crab_CMSDAS_Data_analysis_test0/160718_090558/0000/slimMiniAOD_data_MuEle_1.root' (at nafhh-cms)
> ```
{: .callout}

> ## Question 15
> What is the number of entries in the `mumuMass` plot?
{: .challenge}

# Exercise 16 - Analyzing MiniAOD with an FWLite executable

In this exercise we will make the same `ROOT` file, `myZPeakCRAB.root`, as in [Exercise 15](#exercise-15---analyzing-miniaod-with-an-edanalyzer), but we call it myZPeakCRAB_fwlite.root so that you do not end up overwriting the file previously made in [Exercise 15](#exercise-15---analyzing-miniaod-with-an-edanalyzer).

First, check out the following two packages by doing:

```shell
cd $CMSSW_BASE/src/
git cms-addpkg PhysicsTools/FWLite
git cms-addpkg PhysicsTools/UtilAlgos
```
{: .source}

Next, replace the existing `$CMSSW_BASE/src/PhysicsTools/FWLite/bin/FWLiteWithPythonConfig.cc` with this [FWLiteWithPythonConfig.cc]({{ page.root }}{% link code/FWLiteWithPythonConfig.cc %}). You are simply updating an existing analyzer. Then, create the file [$CMSSW_BASE/src/parameters.py]({{ page.root }}{% link code/parameters.py %}).

> ## Note
> In case you have completed [Exercise Set 3]({{ page.root }}{% link _episodes/03-CMSDataAnalysisSchoolPreExerciseThirdSet.md %}) successfully, put the names and path of the `ROOT` files that you made yourself via submitting CRAB job, instead of those currently in `parameters.py`.
> 
> `parameters.py` will read from area `root://cmseos.fnal.gov//store/user/cmsdas/2021/pre_exercises/Set4/Input/DoubleMuon/`. You should have a similar location from where you can read your [CRAB][crab] output `ROOT` files. You can edit the `parameters.py` file to use the [MiniAOD][miniaod] files you made in [Exercise 13]({{ page.root }}{% link _episodes/03-CMSDataAnalysisSchoolPreExerciseThirdSet.md %}#exercise-13---running-on-dataset-with-crab) by replacing the location of the input files:
> ```
> 'root://cmseos.fnal.gov//store/user/cmsdas/2020/pre_exercises/Set4/Input/DoubleMuon/slimMiniAOD_data_MuEle_1.root', (at cmslpc)
> 'file:/afs/cern.ch/work/d/dmoon/public/CMSDAS_Files/Exe4/slimMiniAOD_data_MuEle_1.root', (at lxplus or Bari) or
> 'file:/cmsdas/data/pre_exercises/Exe4/slimMiniAOD_data_MuEle_1.root', (at KNU) or
> 'file:/pnfs/desy.de/cms/tier2/store/user/your_username/DoubleMuon/crab_CMSDAS_Data_analysis_test0/160718_090558/0000/slimMiniAOD_data_MuEle_1.root' (at nafhh-cms)
> ```
{: .callout}

Then we will compile the code that you just saved by doing:

```shell
cd $CMSSW_BASE/src/
scram b -j 4
```
{: .source}

You should see among the output a line like the one below. If not, it is probable that you haven't compiled the code on which we are working.

```
>> Compiling  /your_path/YOURWORKINGAREA/CMSSW_10_6_4/src/PhysicsTools/FWLite/bin/FWLiteWithPythonConfig.cc
```
{: .output}

After successful compilation, you must run the config file as follows:

```shell
cd $CMSSW_BASE/src/
cmsenv
FWLiteWithPythonConfig parameters.py
```
{: .source}

> ## Note
> Take note of the extra `cmsenv` is to ensure the changes to files in the `bin` subdirectory are picked up in your path.
{: .callout}

> You might get a segfault when running this exercise. Just ignore it; the output `ROOT` file will still be created and be readable.
{: .warning}

> ## Note
> Take a look at how the parameters defined in `parameters.py` get input to the executable code `FWLiteWithPythonConfig.cc`.
{: .callout}

A successful running of the FWLite executable, `FWLiteWithPythonConfig`, results in an output file called `myZPeakCRAB_fwlite.root`.

The output `ROOT` file `myZPeakCRAB_fwlite.root` is a bit different from `myZPeakCRAB.root` made in [Exercise 15](#exercise-15---analyzing-miniaod-with-an-edanalyzer) since we did not make any of the electron histograms. The histograms do have the `mumuMass`, besides, `muonEta`, `muonPhi`, and `muonPt`.

> ## Question 16
> What is the number in entries in the `mumuMass` obtained in [Exercise 16](#exercise-16---analyzing-miniaod-with-an-fwlite-executable)?
{: .challenge}

# Exercise 17 - Fitting the Z mass peak

The main intention of fitting the Z mass peak is to show how to fit a distribution. To do this exercise, you will need the `ROOT` files that you made in [Exercise 15](#exercise-15---analyzing-miniaod-with-an-edanalyzer) and [Exercise 16](#exercise-16---analyzing-miniaod-with-an-fwlite-executable). Make sure you have the `ROOT` file `$CMSSW_BASE/src/myZPeakCRAB.root` ( [Exercise 15](#exercise-15---analyzing-miniaod-with-an-edanalyzer)) or `myZPeakCRAB_fwlite.root` ([Exercise 16](#exercise-16---analyzing-miniaod-with-an-fwlite-executable)). If you have not managed to create at least one of these `ROOT` files, you can get them from the following locations:

> ## File list
> ```
> root://cmseos.fnal.gov//store/user/cmsdas/2020/pre_exercises/Set4/Output/myZPeakCRAB.root # cmslpc
> root://cmseos.fnal.gov//store/user/cmsdas/2020/pre_exercises/Set4/Output/myZPeakCRAB_fwlite.root # cmslpc
> /afs/cern.ch/cms/Tutorials/TWIKI_DATA/CMSDataAnaSch/myZPeakCRAB.root # lxplus or Bari
> ```
{: .solution}

This will allow you to continue with [Exercise 17](#exercise-17---fitting-the-z-mass-peak). For this exercise, we will use the `ROOT` file `myZPeakCRAB.root`. Alternatively, you can use the file `myZPeakCRAB_fwlite.root`, but just make sure to have the right name of the `ROOT` file. The most important factor is that both of these files have the histogram `mumuMass`.

We also ask that you create a [rootlogon.C]({{ page.root }}{% link code/rootlogon.C %}) file in the `$CMSSW_BASE/src/` directory. We will reference this version as opposed to anyone's personalized rootlogon file. This sets up the libraries needed to complete this exercise. 

The different distribution that we would fit to the Z mass peak are:

 - Gaussian

```math
  \begin{displaymath}
   G(x; \mu, \sigma) = \frac{1}{\sqrt{2\pi}\sigma}\exp\left[-\frac{(x-\mu)^2}{2\sigma^2}\right]
  \end{displaymath}
```

 - Relativistic Breit-Wigner

```math
  \begin{displaymath}
   B(m; M, \Gamma) = N \cdot \frac{2}{\pi} \cdot \frac{\Gamma^{2}M^{2}}{(m^{2}-M^{2})^{2}+m^{4}(\Gamma^{2}/M^{2})}
  \end{displaymath}
```

 - Convolution of relativistic Breit-Wigner plus interference term with a Gaussian

```math
  \begin{displaymath}
   P(m) = \int B(m'; M, \Gamma)\cdot G(m-m'; \mu, \sigma) dm'  
  \end{displaymath}
```

> ## Some general remarks about fitting a Z peak
> To fit a generator-level Z peak, a Breit-Wigner fit makes sense. However, reconstructed-level Z peaks have many detector resolutions that smear the Z mass peak. If the detector resolution is relatively poor, then it is usually good enough to fit a Gaussian (since the gaussian detector resolution will overwhelm the inherent Briet-Wigner shape of the peak). If the detector resolution is fairly good, then another option is to fit a Breit-Wigner (for the inherent shape) convolved with a Gaussian (to describe the detector effects). This is in the "no-background" case. If you have backgrounds in your sample (Drell-Yan, cosmics, etc...), and you want to do the fit over a large mass range, then another function needs to be included to take care of this; an exponential is commonly used.
{: .callout}

## Fitting a Gaussian

### Using the inbuild Gaussian in ROOT

### Using a macro of your own in ROOT

### Using a macro in RooFit

## Fitting a Breit-Wigner

### Using a macro in ROOT

### Using a macro in RooFit

## Fitting a Convolution of Gaussian and Breit-Wigner

### Using a macro in RooFit



{% include links.md %}
