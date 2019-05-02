#!/bin/bash

# activate virtualenv
source /home/cmsuser/cms_venv/bin/activate

# allow searching for system headers in current directory
export CPATH=$CPATH:.

# kill proxy service to trigger restart
killall cmsProxyService

# start services
cmsLogService >> /var/log/cms/logservice.log &
cmsRankingWebServer >> /var/log/cms/ranking.log &
cmsResourceService -a 1 >> /var/log/cms/resource.log &