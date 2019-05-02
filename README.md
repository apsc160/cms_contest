# APSC 160 Contest

This contest is designed to run under a modified version of the [cms](https://cms-dev.github.io) contest management system.  The forked repository resides [here](https://github.com/apsc160/cms).  It has been modified to include the following

- includes a custom contest importer, based on the built-in `italy_yaml`, that allows more detailed
  specifications, and can be used to import this contest
- adds a "Student ID" field for users to link to their participation grade
- adds support for displaying markdown directly in a problem statement (based on [this pull request](https://github.com/cms-dev/cms/pull/1086))
- displays contest time in the form `d:hh:mm:ss` rather than simply `hh:mm:ss`
- adds online code editor support for submissions using the [ace editor](https://ace.c9.io/)
- a few bug-fixes

## Installation of CMS

In this guide we assume you will be installing on an Ubuntu machine.  If not, see the [cms installation docs](https://cms.readthedocs.io/en/v1.4/Installation.html) for how to install the necessary prerequisites on your machine.

### Prerequisites

Run the following commands on modern Ubuntu systems to automatically install the necessary prerequisites:
```bash
sudo apt install build-essential postgresql postgresql-client python3.6 \
	 python3.6-dev python3-pip cppreference-doc-en-html cgroup-lite \
	 libcap-dev zip git
```

---

**Note:** for Ubuntu 14.04 and earlier, the versions of `python` and `postgresql` are too outdated for `cms`.  You will need to update `python` to at least version 3.6, and `postgresql` to at least version 9.4.

To update and install `python`,
```
sudo add-apt-repository ppa:jonathonf/python-3.6
sudo apt update
sudo apt install python3.6 python3.6-dev
```

For `postgresql`, run
```
sudo sh -c 'echo "deb http://apt.postgresql.org/pub/repos/apt/ $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list'
wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
sudo apt-get update
sudo apt install postgresql postgresql-client
```

---

### Configure Daemon User and Database

We need to set up users and groups in order to run `cms` safely and allow access to a `postgresql` database.

Create a user with limited permissions that will be used to run `cms`.  In this guide will call this user `cmsuser`.

```
sudo adduser cmsuser
```

Alternatively, you can add a user to the `cmsuser` group explicitly with

```bash
sudo usermod -a -G cmsuser <user>
```

Changes will take affect on next login.  We also need to initialize a database for `cms` to store the contest data.  On Ubuntu, we need to switch to the `postgres` user for this:

```bash
sudo su - postgres
createuser --username=postgres --pwprompt cmsuser
createdb --username=postgres --owner=cmsuser cmsdb
psql --username=postgres --dbname=cmsdb --command='ALTER SCHEMA public OWNER TO cmsuser'
psql --username=postgres --dbname=cmsdb --command='GRANT SELECT ON pg_largeobject TO cmsuser'
exit
```

Remember the password for the new `cmsuser`, as we will need this to configure `cms` after installation.

### Creating a Python Virtual Environment

The `cms` system requires specific versions of several python packages.  To avoid conflicts with our system-installed versions and to ensure the correct version of python is running, we will create a virtual python environment.

Switch to the `cmsuser`,

```bash
su - cmsuser
```

Create and activate a `python3.6` environment

```bash
pip3 install virtualenv
virtualenv -p /usr/bin/python3.6 ~/cms_venv
source ~/cms_venv/bin/activate
```

### Installing CMS

Clone the [forked git repository](https://github.com/apsc160/cms), and navigate inside the main directory.  You will also need to clone the `isolate` submodule, which will run the contestants' programs in an isolated environment.  We then need to build the prerequisites.

```bash
git clone https://github.com/apsc160/cms.git 
cd cms
git submodule update --init
python3 prerequisites.py build
```

Next, we build and install [`isolate`](https://github.com/ioi/isolate.git), the program that allows us to safely run submissions in an isolated environment, as well as install important configuration files.  For this we need to temporarily switch to a `sudo` user and execute the prerequisites install command.

```bash
su <sudo_user> 
sudo python3 prerequisites.py install
exit
```

The script will ask about adding your user to the `cmsuser` group.  You can select `No` for this, since we already created a special `cmsuser`. 

To complete the installation, install the required python packages, then build and install `cms`:

```bash
pip3 install -r requirements.txt
python3 setup.py install
```

---

**Note:**  if your temporary directory is mounted as `noexec` then you may receive a warning about your environment not being able to run compiled executables.  To circumvent this, temporarily redirect the `TMPDIR` to a local location,

```bash
mkdir ~/tmp
export TMPDIR=~/tmp
```

then try again.

---

### Configuring CMS

Modify the configuration file `/usr/local/etc/cms.conf`

Update the `"database"` connection string to include your cms database username and password.  For example,
```bash
"database": "postgresql+psycopg2://cmsuser:your_password_here@localhost:5432/cmsdb",
```

Modify the `"secret_key"` field with a unique random string.  An example of how to generate such a key is described in the corresponding `"_help:"` section.

Modify the `"rankings"` connection string.  Change the username and password to something less obvious.

Edit the file `/usr/local/etc/cms.ranking.conf` to set the same username and password as the previous connection string.

### Initializing CMS

Create the initial database
```bash
cmsInitDB
```

Create a new admin user
```bash
cmsAddAdmin <username> -p
```
You will be prompted to enter a password for your new user.  This is the username and password you will use to log in to the admin webserver to update the contest details manually.

### Importing the Contest

Close the latest version of this contest from Git:
```bash
cd ~
git clone https://github.com/apsc160/cms_contest.git
```

To import the contest, run the following:
```
cmsImportContest -L extended_yaml -i cms_contest
```
This will import all contests and tasks from the `cms_contest` folder and import them in the contest database.

#### Updating an Existing Contest

To update an existing contest (e.g. if the `cms_contest` content has been updated), then use the update flags
```
cmsImportContest -L extended_yaml -i -u -U cms_contest
```
This will import any new tasks, as well as update existing tasks and overall contest details.

### Running the Server

To run the server, we need to ensure the python virtual environment is active, adjust the `CPATH` environment variable to also check local directories (so students can use `#include <DAQlib.h>` instead of `#include "DAQlib.h"`), then start the log, ranking, and resource services:
```bash
source /home/cmsuser/cms_venv/bin/activate
export CPATH=$CPATH:.
cmsLogService >> /var/local/log/cms/logservice.log &
cmsRankingWebServer >> /var/local/log/cms/ranking.log &
cmsResourceService -a 1 >> /var/local/log/cms/resource.log &
```
These commands are all packaged in a bash script within this repository at `cms/start_cms.sh`, which can be run using
```bash
~/cms_contest/cms/start_cms.sh
```

The contest, admin and ranking webservers should all now be up and running, though they must be accessed via their port numbers:

| Server      | Address                |
|-------------|------------------------|
| Contest     | http://localhost:8888/ |
| Admin       | http://localhost:8889/ |
| Leaderboard | http://localhost:8890/ |

#### Apache Proxy Settings

If you would like to access the contest server, admin server, and leaderboard with pretty URL names rather than port numbers, then we can set up an apache webserver to act as a proxy and forward to the correct ports.  Include the following apache configuration to enable proxy forwarding:

```default
 # setup the proxy
<Proxy *>
	Order allow,deny
	Allow from all
</Proxy>
       
ProxyPass /cms/contest/ http://localhost:8888/
ProxyPassReverse /cms/contest/ http://localhost:8888/

ProxyPass /cms/admin/   http://localhost:8889/
ProxyPassReverse /cms/admin/   http://localhost:8889/

ProxyPass /cms/leaderboard/ http://localhost:8890/
ProxyPassReverse /cms/leaderboard/ http://localhost:8890/
```
These settings can be found in this repository under `cms/cms.proxy.conf`.  To enable the proxy configuration for all configured websites, copy the file to your apache configuration folder and create a symbolic link in the `conf-enabled` folder.  Again, you will need `sudo` rights for this:
```bash
su <sudo_user>
sudo cp /home/cmsuser/cms/cms.proxy.conf /etc/apache2/conf-available
sudo ln -s /etc/apache2/conf-available/cms.proxy.conf /etc/apache2/conf-enabled
sudo service apache2 restart
exit
```


This will allow you to access the webservers through the regular port 80 on your host:

| Server      | Address                         |
|-------------|---------------------------------|
| Contest     | https://server/cms/contest/     |
| Admin       | https://server/cms/admin/       |
| Leaderboard | https://server/cms/leaderboard/ |

#### Automatic Start via Cron

In cases where your server may be reset, and you wish to automatically restart the contest server, you can create a simple bash script containing the previous run commands and set it to automatically launch via a `cron` job.  This contest repo contains such a script under the `cms` folder.

Edit the crontab file:
```bash
crontab -e
```
and add the following line at the bottom:
```
  5  5  *   *   *     /home/cmsuser/cms_contest/cms/start_cms.sh
```
This will try to start the webservers every morning at 5:05 AM to ensure they are running.  There is no harm to trying to start them while they are still running.  