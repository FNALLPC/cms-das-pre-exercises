---
title: Setup
questions:
- "What accounts do I need to perform my work on CMS?"
- "How do I obtain and install a grid certificate?"
- "Who can I contact if I need help with the pre-exercises?"
---

# Support

 If you have not used the Linux command line before, you may learn more at [WorkBookBasicLinux](https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookBasicLinux).

## Support email

For CMSDAS@LCP {{ site.year }}, you may e-mail [cmsdasatlpc@fnal.gov](mailto:cmsdasatlpc@fnal.gov) with a detailed description of your problem. The instructors will be happy to help you.

## Mattermost (chat)

There is a dedicated Mattermost team, called CMSDAS@LPC {{ site.year }}, setup to facilitate communication and discussions via live chat (which is also archived). The channel is hosted by the [CERN Mattermost instance](https://mattermost.web.cern.ch).

If you have never used Mattermost at CERN, please know that you will need your CERN login credentials (SSO) and you will need to join the private CMSDAS@LPC {{ site.year }} team in order to be able to see (or find using the search channels functionality) the channels setup for communications related to the school.

If you already have used Mattermost at CERN, please know that when you click direct links to channels (as you will find below) that are within the CMSDAS@LPC {{ site.year }} team, you **may** be redirected to the last Mattermost team you used. If this happens, remember to click the [signup link to join the CMSDAS@LPC {{ site.year }} team](https://mattermost.web.cern.ch/signup_user_complete/?id=kayhqykwg3fhuc7gp1j4aw941c) to switch to the correct team from which you should be able to see the individual channels. If that still doesn't work, remove all cookies associated with cern.ch and restart your browser.

The [PreExercisesChannel](https://mattermost.web.cern.ch/cmsdaslpc{{ site.year }}/channels/preexercises) will be available once you join or switch to the CMSDAS@LPC {{ site.year }} team!

Note that you can access Mattermost via browser or you can download the corresponding application running standalone on your laptop or smartphone. The laptop application does not work with CERN certificate login.

# Obtain a Computer Account

To get a CERN account, please have a look at [Get Account at CERN](https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookGetAccount). Obtaining a CERN account can be time-consuming and requires response from people at CERN during CERN business hours. CERN is closed Dec. 19, 2020 - Jan. 3, 2021. CERN account application starts with the institutional team leader filling out a pre-registration form, so your institutional team leader also needs to be available for this task.

> ## NOTE
> If you need an account elsewhere, you need to contact your local cluster admins and follow their instructions.
{: .callout}

> ## Site specific instructions
>   * [LPC/Fermilab](http://www.uscms.org/uscms_at_work/computing/getstarted/getaccount_fermilab.shtml) - this can occasionally take some time and also requires people to be available to approve accounts, start the request early! 
>     * [Configure your laptop to connect to the cmslpc-sl7 LPC UAF cluster at Fermilab](http://uscms.org/uscms_at_work/physics/computing/getstarted/uaf.shtml)
>     * [Windows Kerberos at FNAL](https://fermi.service-now.com/kb_view.do?sysparm_article=KB0011316)
{: .callout}

Here are some additional links in case you are using Windows:
  * [Hints for setting up Cygwin](http://uscms.org/uscms_at_work/physics/computing/getstarted/uaf.shtml#windowsXServers)
  * How to install and configure [PuTTy](http://uscms.org/uscms_at_work/physics/computing/getstarted/uaf.shtml#windowsKerberosPuTTY)

> ## Warning
> If you are attending CMSDAS at the LPC, you should do the pre-exercises on the **cmslpc-sl7** cluster using the laptop you intend to bring to the LPC. You will also have to register that device on the FNAL network before coming (using your Fermilab services username and password), see link on the left bar of the [CMSDAS@LPC2020 indico agenda](https://indico.cern.ch/e/cmsdas2020).
{: .caution}

## Obtain a Grid Certificate and CMS VO Registration

A Grid Certificate and CMS VO registration will be needed for the next set of exercises. The registration process can be time-consuming (actions by several people are required), so it is important to start it as soon as possible. There are two main requirements which can be simply summarized: A certificate ensures that you are who you claim to be. A registration in the VO recognizes your (identified by your certificate) as a member of CMS. Use the following link for this: [Fermilab guide to getting CMS CERN grid certificate and CMS VO](http://uscms.org/uscms_at_work/physics/computing/getstarted/get_grid_cert.shtml). Both are needed to submit jobs to the grid and access files remotely using XRootD. Make sure you follow any additional instructions for US-CMS users.

## Obtain a GitHub Account

Since Summer 2013, most of the CMS software are hosted on [GitHub]. [GitHub] is a Git repository web-based hosting service, while Git is a distributed version control system. In your future analysis work, version control of your analysis code will become a very important task and git will be very useful. A small git tutorial will wait for you in the [fifth exercise set]({{ page.root }}{% link _episodes/05-CMSDataAnalysisSchoolPreExerciseFifthSet.md %}).

In order to checkout and develop CMS software, you will need a github account, which is free.
  * In case you don’t have one already, simply go to [https://github.com/join](https://github.com/join) and follow the instructions to create a new account. Make sure you use a username people can recognize you easily or to specify your real name.
  * In case you already have an account you can simply use the "[Sign in](https://github.com/login)"" dialog and put your username and password.
  * Make sure you register your ssh key in [GitHub]. You can register more than one ssh key and it's usually a good idea to do so for every computer/cluster on which you regularly work (i.e. you laptop, cmslpc-sl7, your university cluster, etc.). You don't need to use an ssh-agent, but you can try if you want to. For more about ssh-agents, see [CMSGitTutorial#SSH_agent_in_logon_file](CMSGitTutorial#SSH_agent_in_logon_file).
  * You will learn more about [GitHub] in the [fifth set of exercises]({{ page.root }}{% link _episodes/05-CMSDataAnalysisSchoolPreExerciseFifthSet.md %}). 

{% include links.md %}
