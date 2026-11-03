---
title: "CMSDAS Pre-Exercise 2: Using the cmslpc cluster"
teaching: 0
exercises: 30
questions:
- "How do I log in to the cmslpc cluster?"
- "How do I run commands and edit files on cmslpc?"
- "How do I copy files from EOS?"
objectives:
- "Log in to cmslpc with kerberos and SSH."
- "Run a script and edit a file on cmslpc."
- "Copy a file from EOS to your nobackup area."
keypoints:
- "Log in with `kinit <username>@FNAL.GOV` followed by `ssh -Y <username>@cmslpc-el9.fnal.gov`."
- "Use `~/nobackup` for your work; your home directory is small."
- "EOS has its own commands (`eosls`, `eosmkdir`, `xrdcp`) and addresses files by LFNs like `/store/user/...`."
---

{% include submit.md episode=2 %}

## Introduction
Your laptop can only do so much: CMS analyses run over far more data than fits on it.
In this episode you will use the **cmslpc** computing cluster at Fermilab, which you will use throughout CMSDAS and possibly for your own analysis.
Notes for CERN `lxplus` users are included where things differ.

## The basics
cmslpc has **interactive nodes**, which you log in to with SSH, and many more **worker nodes** for large-scale batch computing.
The nodes run [AlmaLinux 9](https://almalinux.org/) (`el9`), a free OS compatible with Red Hat Enterprise Linux.

Every user gets three storage areas:

| Area | Path | Size | Notes |
|---|---|---|---|
| Home | `/uscms/home/<username>` | 2 GB | Small: keep only config files here |
| nobackup | `~/nobackup` (links to `/uscms_data/d[1-3]/<username>`) | 200 GB | Your main work area; **not backed up** |
| EOS | `/store/user/<username>` | 2 TB | Special filesystem, see [below](#using-the-eos-filesystem) |

`lxplus` is set up similarly, with different paths and quotas. `lxplus.cern.ch` points to AlmaLinux 9 nodes.

## Logging in
cmslpc uses [kerberos](https://en.wikipedia.org/wiki/Kerberos_(protocol)) for authentication and SSH for login.
If you have never logged in from this computer, first set up `krb5.conf` and `~/.ssh/config` following the [cmslpc prerequisites](https://www.uscms.org/uscms_at_work/computing/getstarted/uaf.shtml#prerequisites).
(New to SSH? See the [HSF SSH lesson](https://hsf-training.github.io/hsf-training-ssh-webpage/).)

Then, on your own computer, get a kerberos ticket and log in:

```shell
kinit <YourUsername>@FNAL.GOV        # lxplus: kinit <YourUsername>@CERN.CH
ssh -Y <YourUsername>@cmslpc-el9.fnal.gov   # lxplus: ssh -Y <YourUsername>@lxplus.cern.ch
```
{: .source}

`kinit` asks for your [Fermilab kerberos password](https://uscms.org/uscms_at_work/computing/getstarted/password_fermilab.shtml#passwordObtain) and is valid for 24 hours.
If you see a welcome message and a prompt, you're in: commands now run on cmslpc.
If you get an error, re-check your [kerberos configuration](https://uscms.org/uscms_at_work/physics/computing/getstarted/uaf.shtml), then post the error on Mattermost.

## Running simple commands on cmslpc
These steps only work on **cmslpc-el9**. Experienced users can breeze through, but please still submit your answers so we can follow everyone's progress.

Make a folder for your CMSDAS work, copy in the `runThisCommand.py` script, and run it with these exact arguments (copy-and-paste them):

```shell
mkdir ~/nobackup/cmsdas
cd ~/nobackup/cmsdas
cp ~cmsdas/preexercises/runThisCommand.py .
python3 runThisCommand.py "asdf;klasdjf;kakjsdf;akjf;aksdljf;a" "sldjfqewradsfafaw4efaefawefzdxffasdfw4ffawefawe4fawasdffadsfef"
```
{: .source}

It prints your username followed by a string unique to you. For example, for user `gbenelli`:

```
success: gbenelli toraryyv
```
{: .output}

> ## Seeing an error instead?
> - `Error: You must provide the secret key`: you left out the two arguments.
> - `Error: You didn't paste the correct input string`: the arguments were mistyped; copy-and-paste them.
> - `No such file or directory` or `Unknown user`: you are not on cmslpc-el9 (for example, you ran it on your laptop).
{: .callout}

> ## Question 2.1
> Enter the alphanumeric string unique to your username in the answer form.
{: .challenge}

## Editing files on cmslpc
You'll edit code on cmslpc constantly. Common options:

- A terminal editor directly on cmslpc: `nano` (simplest), `vim`, or `emacs -nw` (plain `emacs` opens a slow GUI over SSH).
- A desktop editor such as VS Code with a remote/SSH plugin, which shows your cmslpc folder as if it were local.
- Editing on your laptop and copying with `scp`/`sftp`.

For this exercise, use a terminal editor on cmslpc. (New to `vim`? Try this [interactive tutorial](https://openvim.com/).)
Copy the [editThisCommand.py]({{ page.root }}{% link code/editThisCommand.py %}) script:

```shell
cd ~/nobackup/cmsdas
cp ~cmsdas/preexercises/editThisCommand.py .
```
{: .source}

Open it (e.g. `nano editThisCommand.py`). Line 11 deliberately raises an error. Add a `#` at the start of the line to turn it into a comment:

```python
#raise RuntimeError("You need to comment out this line with a #")
```
{: .source}

Save and quit (nano: `ctrl+o`, `ctrl+x`; vim: `i` to type, then `Esc` and `:wq`; emacs: `ctrl+x ctrl+s`, `ctrl+x ctrl+c`), then run:

```shell
./editThisCommand.py
```
{: .source}

If the edit worked, you'll see a line like `success:  gbenelli 0x6D0DB4E0`.
If you see `RuntimeError: You need to comment out this line with a #`, the edit wasn't saved.

> ## Question 2.2
> Enter the line beginning with "success", printed by `./editThisCommand.py`, in the answer form.
{: .challenge}

## Using the EOS filesystem
EOS is your largest storage area, but it is not a normal Unix folder and has its own commands.
Files on EOS are named by **logical filenames** (LFNs), which start with `/store/...`.
The essential commands are below; see [Using EOS at LPC](https://uscms.org/uscms_at_work/computing/LPC/usingEOSAtLPC.shtml) for everything else.

| Unix | EOS on cmslpc | Example |
|---|---|---|
| `ls` | `eosls` | `eosls -alh /store/user/cmsdas/preexercises/` |
| `mkdir`, `mv` | `eosmkdir`, `eosmv` | |
| `cp` | `xrdcp` | `xrdcp root://cmseos.fnal.gov//store/user/<file> .` |

The `eos*` commands are cmslpc shortcuts for `eos root://cmseos.fnal.gov ...`; run `alias eosls` to see the full command, which you need on other clusters.
In `xrdcp`, the `root://cmseos.fnal.gov` prefix names the EOS instance. lxplus has several, such as `root://eoscms.cern.ch` (CMS data) and `root://eosuser.cern.ch` (user data).

> ## Question 2.3
> Copy a small file from EOS to your nobackup area. It holds 10,000 simulated $Z\rightarrow\mu^+\mu^-$ events in the CMS NanoAOD format, and later episodes use it, so keep it.
>
> ```shell
> cd ~/nobackup/cmsdas/
> xrdcp root://cmseos.fnal.gov//store/user/cmsdas/preexercises/DYJetsToLL_M50_NANOAOD.root .
> ls -lh DYJetsToLL_M50_NANOAOD.root
> ```
> {: .source}
>
> How big is the file? (It's the large number in the `ls -lh` output.) Enter it in the answer form.
{: .challenge}

{% include links.md %}
