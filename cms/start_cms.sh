#!/bin/bash

# activate virtualenv
source /home/cmsuser/cms_venv/bin/activate

# allow searching for system headers in current directory
export CPATH=$CPATH:.

# kill proxy service to trigger restart
killall cmsProxyService

# start services
cmsLogService >> /var/local/log/cms/logservice.log &
cmsRankingWebServer >> /var/local/log/cms/ranking.log &
cmsResourceService -a 1 >> /var/local/log/cms/resource.log &