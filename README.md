# APSC 160 Contest

This contest is designed to run under a modified version of the [cms](https://cms-dev.github.io) contest management system.  The forked repository resides [here](https://github.com/apsc160/cms).  It has been modified to include the following

- adds a "Student ID" field for users to link to their participation grade
- adds support for displaying markdown directly in problem statements
- displays contest time in the form `d:hh:mm:ss` rather than simply `hh:mm:ss`
- a few bug-fixes

## Installation of CMS

In this guide we assume you will be installing on an Ubuntu machine.  If not, see the [cms installation docs](https://cms.readthedocs.io/en/v1.4/Installation.html) for how to install the necessary prerequisites on your machine.

### Prerequesities

Run the following `apt` commands on modern Ubuntu systems to automatically install the necessary prerequisites:
```bash
sudo apt install build-essential postgresql postgresql-client python3 \
     cppreference-doc-en-html cgroup-lite libcap-dev zip git
```
```bash
sudo apt install python3-setuptools python3-tornado python3-psycopg2 \
     python3-sqlalchemy python3-psutil python3-netifaces python3-crypto \
     python3-six python3-bs4 python3-coverage python3-mock python3-requests \
     python3-werkzeug python3-bcrypt python3-chardet patool python3-babel \
     python3-xdg python3-future python3-jinja2 python3-pip python3-gevent
```

<aside class=notice markdown="1" style="background-color:#888855; padding: 10px">

If `apt` complains about not being able to find `python3-gevent` (e.g. Ubuntu 14.04), then install it through pip:
```bash
sudo pip3 install --upgrade pip
sudo pip3 install gevent
```

</aside>

### Contest Database

We to to set up users and groups so that we can run `cms` safely, and allow access to a `postgresql` database.

Create a user with limited permissions that will be used to run `cms`.  In this guide will call this user `cmsuser`.

```
sudo adduser cmsuser
```

Note the following warning from the [cms documentation](https://cms.readthedocs.io/en/v1.4/Installation.html#preparation-steps):


<div class=warning style="background-color: #885555; padding: 10px">
<strong>Warning:</strong>
<p>
Users in the group cmsuser will be able to launch the isolate program with root permission. They may exploit this to gain root privileges. It is then imperative that no untrusted user is allowed in the group cmsuser.
<p>
</div>

Alternatively, you can add a user to the `cmsuser` group explicitly with
```bash
sudo usermod -a -G cmsuser <user>
```
Changes will take affect on next login.

### Installing CMS

You may wish to switch to the `cmsuser`, and install `cms` in the user's home directory.
```bash
su cmsuser
cd ~
```
Clone the [forked git repository](https://github.com/apsc160/cms), and navigate inside the main directory.  You will also need to clone the `isolate` submodule, which will run the constestants' programs in an isolated environment.
```bash
git clone https://github.com/apsc160/cms.git 
cd cms
git submodule update --init
```


------
Build the prerequisites:
```bash
python3 prerequisites.py build
```
Add the `isolate` folder to the system path, and the current directory to python's path:
```bash
export PATH=$PATH:`pwd`/isolate:`pwd`/scripts
export PYTHONPATH=`pwd`
```
Copy the configuration files to the local `config` directory:
```bash
cp config/cms.conf.sample config/cms.conf
cp config/cms.ranking.conf.sample config/cms.ranking.conf
```
Set `isolate` to be owned by root, and set its `suid` bit.  If you are currently running as `cmsuser`, then you may need to first switch to a `sudo` user.
```
sudo chown root:cmsuser isolate/isolate
sudo chmod u+s isolate/isolate
```

------
Build and install the prerequisites:
```bash
sudo python3 prerequisites.py install
```


# Installing the contest
 Copy the `DAQlib.h` header