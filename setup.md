---
title: Setup
questions:
- "What accounts do I need to perform my work on CMS?"
- "How do I obtain and install a grid certificate?"
- "Who can I contact if I need help with the pre-exercises?"
---


## Mattermost (chat)

There is a dedicated Mattermost team, called [CMSDAS@LPC {{ site.year }}](https://mattermost.web.cern.ch/signup_user_complete/?id=xywbon1zutbqj8a53rzqomrp9r), setup to facilitate communication and discussions via live chat (which is also archived). The channel is hosted by the [CERN Mattermost instance](https://mattermost.web.cern.ch).

If you have never used Mattermost at CERN, please know that you will need your CERN login credentials (SSO) and you will need to join the private CMSDAS@LPC {{ site.year }} team in order to be able to see (or find using the search channels functionality) the channels setup for communications related to the school.

If you already have used Mattermost at CERN, please know that when you click direct links to channels (as you will find below) that are within the CMSDAS@LPC {{ site.year }} team, you **may** be redirected to the last Mattermost team you used. If this happens, remember to click the [signup link to join the CMSDAS@LPC {{ site.year }} team](https://mattermost.web.cern.ch/signup_user_complete/?id=xywbon1zutbqj8a53rzqomrp9r) to switch to the correct team from which you should be able to see the individual channels. If that still doesn't work, remove all cookies associated with cern.ch and restart your browser.

The [PreExercisesChannel](https://mattermost.web.cern.ch/cmsdaslpc{{ site.year }}/channels/preexercises) will be available once you join or switch to the CMSDAS@LPC {{ site.year }} team!

Note that you can access Mattermost via browser or you can download the corresponding application running standalone on your laptop or smartphone. The laptop application does not work with CERN certificate login.

## Support email

For CMSDAS@LPC {{ site.year }}, you may e-mail [cmsdasatlpc@fnal.gov](mailto:cmsdasatlpc@fnal.gov) with a detailed description of your problem. The instructors will be happy to help you.

# Obtain a Computer Account

To get a CERN account, please have a look at [Get Account at CERN](https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookGetAccount). Obtaining a CERN account can be time-consuming and requires response from people at CERN during CERN business hours. CERN is closed Dec. 22, 2021 - Jan. 4, 2022. CERN account application starts with the institutional team leader filling out a pre-registration form, so your institutional team leader also needs to be available for this task.

> ## Site specific instructions
>   * [LPC/Fermilab](http://www.uscms.org/uscms_at_work/computing/getstarted/getaccount_fermilab.shtml) - this can take some time (up to 4-6 weeks!) and also requires people to be available to approve accounts, start the request early!
>     * [Configure your laptop to connect to the cmslpc-sl7 LPC UAF cluster at Fermilab](http://uscms.org/uscms_at_work/physics/computing/getstarted/uaf.shtml)
>     * [Windows Kerberos at FNAL](https://fermi.servicenowservices.com/wp/?id=kb_article&sysparm_article=KB0011316)
{: .callout}

Here are some additional links in case you are using Windows:
  * [Hints for setting up Cygwin - preferred](http://uscms.org/uscms_at_work/physics/computing/getstarted/uaf.shtml#windowsXServers)
  * How to install and configure [PuTTy](http://uscms.org/uscms_at_work/physics/computing/getstarted/uaf.shtml#windowsKerberosPuTTY)

> ## Warning
> If you are attending CMSDAS at the LPC, you should do the pre-exercises on the **cmslpc-sl7** cluster using the computer you intend to use at CMSDAS.
{: .caution}

## Obtain a Grid Certificate and CMS VO Registration

A Grid Certificate and CMS VO registration will be needed for the next set of exercises. The registration process can be time-consuming (actions by several people are required), so it is important to start it as soon as possible. There are two main requirements which can be simply summarized: A certificate ensures that you are who you claim to be. A registration in the VO recognizes you (identified by your certificate) as a member of CMS. Use the following link for this: [Fermilab guide to getting CMS CERN grid certificate and CMS VO](http://uscms.org/uscms_at_work/physics/computing/getstarted/get_grid_cert.shtml). Both are needed to submit jobs to the grid and access files remotely using XRootD. Make sure you follow any additional instructions for US-CMS users.

## Obtain a GitHub Account

Most CMS software is hosted on [GitHub]. [GitHub] is a Git repository web-based hosting service, while git is a distributed version control system. In your future analysis work, version control of your analysis code will become a very important task and git will be very useful. 

In order to checkout and develop CMS software, you will need a github account, which is free.
  * In case you don’t have one already, simply go to [https://github.com/join](https://github.com/join) and follow the instructions to create a new account. Choose your username wisely, ideally based on your actual name, as it will be used to sign all of your contributions to CMS code! 
  * In case you already have an account you can simply use the "[Sign in](https://github.com/login)" dialog and put your username and password.
  * Make sure you register an SSH key in [GitHub], following [these instruction](https://docs.github.com/en/authentication/connecting-to-github-with-ssh). Remember, when you generate an SSH key, two files are generated; the public key (ending in `.pub`) is uploaded to github.com, while the private key (not ending in `.pub`) is put on cmslpc at `~/.ssh/`. Make sure the permissions of your private key are set using `chmod 600 ~/.ssh/id_rsa`. You can register more than one SSH key and it's usually a good idea to do so for every computer/cluster on which you regularly work (i.e. you laptop, cmslpc-sl7, your university cluster, etc.). You don't need to use an ssh-agent, but you can try if you want to. For more about ssh-agents, see [CMSGitTutorial#SSH_agent_in_logon_file](https://twiki.cern.ch/twiki/bin/view/CMSPublic/CMSGitTutorialPublic#SSH_agent_in_logon_file).
  * You may also find it useful to launch `ssh-agent` at login time. Instructions are at https://twiki.cern.ch/twiki/bin/view/CMSPublic/CMSGitTutorialPublic#bash .


## Windows specific setup

If you would like to use cygwin, you will need to install [winpty](https://github.com/rprichard/winpty) and prefix your docker command like `winpty docker`.
Windows Subsystem for Linux can also be used; once installed (whichever flavor of Linux you prefer), you can largely follow the Unix instructions. 

{% include links.md %}
