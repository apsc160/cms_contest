
#### Hacking Ubuntu 14.04

Install python3.6
```bash
sudo add-apt-repository ppa:jonathonf/python-3.6
sudo apt update
sudp apt install python3.6
```

Install Postgresql >= 9.4
```
sudo sh -c 'echo "deb http://apt.postgresql.org/pub/repos/apt/ $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list'
wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
sudo apt-get update
sudo apt install postgresql
```

### Configuring the Database

```bash
sudo su - postgres
```
Decide on a password for database access for user `cmsuser`.  We will need to modify the configuration file later.

```bash
createuser --username=postgres --pwprompt cmsuser
createdb --username=postgres --owner=cmsuser cmsdb
psql --username=postgres --dbname=cmsdb --command='ALTER SCHEMA public OWNER TO cmsuser'
psql --username=postgres --dbname=cmsdb --command='GRANT SELECT ON pg_largeobject TO cmsuser'
```

### Python Dependencies

Cups for pycups requirement
```bash
sudo apt-get install python3.6 python3.6-dev libcups2-dev
```

Create virtual environment
```bash
sudo pip3 install virtualenv
```

From the `cmsuser` account
```bash
virtualenv -p /usr/bin/python3.6 ~/cms_venv
source ~/cms_venv/bin/activate
```

Redirect temporary folder
```bash
mkdir ~/tmp
export TMPDIR=~/tmp
```

Install python requirements
```bash
cd ~/cms
pip3 install -r requirements.txt
```

### Configuration

Modify the configuration file `config/cms.conf`

Update the `"database"` connection string to include your cms database username and password.  For example,
```bash
"database": "postgresql+psycopg2://cmsuser:your_password_here@localhost:5432/cmsdb",
```

Modify the `"secret_key"` field with a unique random string.  An example of how to generate such a key is described in the corresponding `"_help:"` section.

Modify the `"rankings"` connection string.  Change the username and password to something less obvious.

Edit the file `config/cms.ranking.conf` to set the same username and password as the previous connection string.

### Initializing CMS

```bash
export PATH=$PATH:~/cms/scripts:~/cms/isolate
export PYTHONPATH=~/cms
export TMPDIR=~/tmp
python3 setup.py install
```

Create the initial database
```bash
cmsInitDB
```

Create an admin user
```bash
python3 cms/cmscontrib/AddAdmin.py <username>
```
This will generate a random password for you.  You can create a new one throu
