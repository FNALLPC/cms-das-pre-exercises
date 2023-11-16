---
title: "CMSDAS Pre-Exercise 2: Using the cmslpc cluster"
teaching: 0
exercises: 10
questions:
- "Learn how to use the CMSLPC cluster"
objectives:
- "Learn how to use the CMSLPC cluster"
keypoints:
- "Learn how to use the CMSLPC cluster"
---

> ## Questions
> For this lesson, please submit your answers using [Google Form 2][Set2_form].
{: .challenge}

# Introduction
In the previous lesson, you learned how to use Unix on your personal computer. 
However, the CMS detector produces more than 500 terabytes of data per second, so there's only so much you can do on your laptop.
In this lesson, we will learn how to use the cmslpc computing cluster, which you will use extensively during CMSDAS and possibly for your actual analysis work as well. 
Information for lxplus users is also provided, where appropriate.

# The basics
The `cmslpc` cluster consists of a large number of "interactive nodes," which users login to via SSH, and an even larger number of "worker nodes," which are used for large-scale "batch" computing. The cluster currently uses the [Scientific Linux 7](https://scientificlinux.org/) OS, which is a Fermilab rebuild of RedHat Enterprise Linux (note: SL7 is quite old, and the whole LHC community is currently migrating to AlmaLinux 8/9. This will happen mid-2024; but don't worry about it too much, not much will change for us end users). 
Users are allocated storage space in a few places: (1) a small home directory (2 GB) at `/uscms/home/username`, ; (2) a medium storage directory at `/uscms_data/d[1-3]/dryu`, which is softlinked in your home directory at `/uscms/home/username/nobackup` (200 GB, not backed up!), and (3) a large storage directory on EOS (2 TB) (special filesystem, more info later in this lesson). 

The `lxplus` cluster is configured similarly, with slightly different paths and quotas allocated to users. 

# Logging in
Let's try logging in to `cmslpc` using SSH. SSH is a very widely used program for logging into remote Unix clusters; you can check out the [HSF SSH exercise](https://hsf-training.github.io/hsf-training-ssh-webpage/) to learn more, but for now you can just follow the commands in this exercise. The authentication for cmslpc uses kerberos (your university cluster may allow simple password login or certificate login, which are not covered here). 


First, if you have not configured SSH and kerberos on your own computer, please follow [these directions](https://uscms.org/uscms_at_work/computing/getstarted/uaf.shtml). Once you have the cmslpc-specific SSH and kerberos configuration, execute the following command in the terminal on your own computer:

```shell
kinit <YourUsername>@FNAL.GOV
# kinit <YourUsername>@CERN.CH for lxplus users
```

Enter the [kerberos password][https://uscms.org/uscms_at_work/computing/getstarted/password_fermilab.shtml#passwordObtain] for your Fermilab account. You now have login access to cmslpc for 24 hours. If you get an error message, double-check that you [configure kerberos properly](https://uscms.org/uscms_at_work/physics/computing/getstarted/uaf.shtml), or head to Mattermost for help. 

Next, execute the following to login:

```shell
ssh -Y <YourUsername>@cmslpc-sl7.fnal.gov
# ssh -Y <YourUsername>@lxplus7.cern.ch for lxplus users
```

If you see a welcome message followed by a return to a command prompt, congratulations, you have successfully logged in! The commands you enter into the command prompt will now be executed on the cmslpc interactive node. If you see an error message instead, something has probably gone wrong with the authentication; please head to Mattermost and post your error message, and an instructor can help you out. 

# Running simple commands on cmslpc

Note: this exercise will only work on **cmslpc-sl7**.

In this exercise, we will run a few simple commands on cmslpc. At the end, you will type an answer into a spreadsheet (experienced users should feel free to breeze through, but please do upload your answer so we can follow everyone's progress). 

First, make a folder for your CMSDAS work, and `cd` into that directory:
```shell
mkdir ~/nobackup/cmsdas
cd nobackup/cmsdas
```
{: .source}


Use the following command to copy the `runThisCommand.py` script:
```shell
cp ~cmsdas/preexercises/runThisCommand.py .
```
{: .source}

 Next, cut and paste the following and then hit return:
 ```shell
python3 runThisCommand.py "asdf;klasdjf;kakjsdf;akjf;aksdljf;a" "sldjfqewradsfafaw4efaefawefzdxffasdfw4ffawefawe4fawasdffadsfef"
 ```
{: .source}

 The response should be your username followed by alphanumeric string of characters unique to your username, for example for a user named `gbenelli`:

```
success: gbenelli toraryyv
```
{: .output}

If you executed the command without copy-pasting (i.e. only `./runThisCommand.py` without the additional arguments) the command will return:

```
Error: You must provide the secret key
```
{: .output}

Alternatively, copying incorrectly (i.e. different arguments) will return:

```
Error: You didn't paste the correct input string
```
{: .output}

If you are not running on cmslpc-sl7 (for example locally on a laptop), trying to run the command will result in:

```
bash: ./runThisCommand.py: No such file or directory
```
{: .output}

or (for example):

```
Unknown user: gbenelli.
```
{: .output}

> ## Question 2.1
> Copy-and-paste the alphanumeric string of characters unique to your username in the Google form.
{: .challenge}

# Editing files on cmslpc

The purpose of this exercise is to ensure that the user can edit files. We will first copy and then edit the [editThisCommand.py]({{ page.root }}{% link code/editThisCommand.py %}) script. 

Users of cmslpc have several options for editing remote files. Here are a few examples:

- Edit files directly on cmslpc using a terminal-based code editor, such as `nano`, `emacs` (opens a GUI by default, which is slow over SSH; use `emacs -nw` to get a terminal-based editor instead), or `vim`. `emacs` and `vim`, in particular, have lots of features for code editing, but also have a steep learning curve.
- Edit files on your own computer in the terminal (with the same programs), and upload using, e.g., `sftp myscript.py username@cmslpc-sl7.fnal.gov:my/folder`. 
- Use an application like Visual Studio Code or Sublime Text, either directly on cmslpc (using a remote filesystem plugin, which makes your directory on cmslpc appear as a folder on your computer) or on your own computer (using an SFTP plugin to automatically upload files to cmslpc). These also have lots of features, and are somewhat easier to learn than `emacs` or `vim`.

For the sake of this lesson, will will simply edit a file directly on cmslpc, using `nano`, `emacs`, or `vim`. On the **cmslpc-sl7** cluster, run:

```shell
cd ~/nobackup/cmsdas
cp ~cmsdas/preexercises/editThisCommand.py .
```
{: .source}

Then open `editThisCommand.py` with your favorite editor (e.g. `emacs -nw editThisCommand.py`). 
The 11th line of this python script throws an error, meaning that python prints an error message and ends the program immediately. 
For this exercise, add a `#` character at the start of the 11th line, which turns the line of code into a comment that is skipped by the python interpreter. 
Specifically, change:

```python
# Please comment the line below out by adding a '#' to the front of
# the line.
raise RuntimeError("You need to comment out this line with a #")
```
{: .source}

to:

```python
# Please comment the line below out by adding a '#' to the front of
# the line.
#raise RuntimeError("You need to comment out this line with a #")
```
{: .source}

(For vim users: you need to press "i" to insert text.) Save the file (e.g. in emacs, type `ctrl+x ctrl+s` to save, `ctrl+x ctrl+c` to quit the editor; in vim, press ESC to exit insert mode, the ":wq" to save and exit) and execute the command:

```shell
./editThisCommand.py
```
{: .source}

If this is successful, the result will be:

```
success:  gbenelli 0x6D0DB4E0
```
{: .output}

If the file has not been successfully edited, an error message will result such as:

```
Traceback (most recent call last):
  File "./editThisCommand.py", line 11, in ?
    raise RuntimeError, "You need to comment out this line with a #"
RuntimeError: You need to comment out this line with a #
```
{: .output}

> ## Question 2.2
> Copy-and-paste the line beginning with "success", resulting from the execution of `./editThisCommand.py`, into the Google form.
{: .challenge}


# Using the EOS filesystem
Your biggest storage on cmslpc is the EOS filesystem, which behaves differently from a normal Unix folder. 
In particular, EOS has dedicated commands for interacting with the filesystem, rather than the usual `ls`, `cp`, `mkdir`, etc. 
Also, files are addressed using so-called "logical filenames" (LFNs), which you can think of as their location inside EOS, rather than their absolute location (or physical filename, PFN). 
The LFNs usually start with `/store/...`.
[Click here](https://uscms.org/uscms_at_work/computing/LPC/usingEOSAtLPC.shtml) for the full documentation; here are a few essential commands. 

- On cmslpc, the equivalent of `ls` is `eosls`: for example, `eosls /store/user/cmsdas/2024`. This is actually a cmslpc-specific alias for `eos root://cmseos.fnal.gov ls`; on other clusters, you'll have to use this full command. A useful flag is `eosls -alh`, which will print folder and file sizes. 
- Similarly to `ls`, the cmslpc-specific equivalents of `mkdir` and `mv` are `eosmkdir` and `eosmv`. (You can do `alias eosmkdir` to see the full command behind the alias.)
- The equivalent of `cp` is `xrdcp`: for example, `xrdcp root://cmseos.fnal.gov//store/user/cmsdas/2024/preexercises/DYJetsToLL_M50_NANOAOD.root .`. The `root://cmseos.fnal.gov` bit tells `xrdcp` which EOS instance to use (only one instance for cmslpc users; lxplus has several, e.g., `root://eoscms.cern.ch` for CMS data and `root://eosuser.cern.ch` for user data). 

> ## Question 2.3
> We will copy a small file from EOS to your nobackup area, containing 10,000 simulated $Z\rightarrow\mu^+\mu^-$ events in the CMS NanoAOD format. We will use this file in later exercises, so make sure not to lose track of it. 
> 
> Execute the following:
> 
> ```shell
> cd ~/nobackup/cmsdas/
> xrdcp root://cmseos.fnal.gov//store/user/cmsdas/2024/preexercises/DYJetsToLL_M50_NANOAOD.root .
> ```
> {: .source}
> 
> Using `ls -lh DYJetsToLL_M50_NANOAOD.root`, how big is this file? (It's the large number.) Write the answer in the Google form. 
{: .challenge}

[Set2_form]: https://forms.gle/N8C48nTWoBk3omJKA
