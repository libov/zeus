#!  /bin/bash
#-------------------------------------- options --------------------------------------
WEBINFOPATH=/data/zenith226a/libov/amadeus/events/rgap30/web.info.files/
#CONFIGSET='.BGF.0304p .BGF.05e.part1 .BGF.05e.part2 .BGF.05e.part3 .BGF.06e .BGF.0607p.part1 .BGF.0607p.part2'
#CONFIGSET='.BGF.0304p05e06e.bb.no_pT_hat'
#CONFIGSET='.BGF.05e.bb.no_pT_hat'
#CONFIGSET='.BGF.05e.part.bb.no_pT_hat'
#CONFIGSET='.BGF.bb.noQEDEW.pfde06'
#CONFIGSET='.BGF.dummy'
#CONFIGSET='.BGF.0607p.part1'
#CONFIGSET='.BGF.cc.noQEDEW.pfde06'
#CONFIGSET='.BGF.0304p'  # 31/01/2011
CONFIGSET='.BGF.0304p.bb.no_pT_hat'  # 03/07/2011
#-------------------------------------------------------------------------------------
rm -f generate_zarah.sh
for CONFIG in $CONFIGSET
do
	echo processing $CONFIG
	echo "#!  /bin/bash" > generate_zarah.sh
	echo python steer.py -f info$CONFIG -p $WEBINFOPATH -c $CONFIG >> generate_zarah.sh
	chmod a+x generate_zarah.sh
	zarah-jobsub -q M -s generate_zarah.sh ../run_rapgap30 *.py *.cfg
	rm -f generate_zarah.sh
done
#-------------------------------------------------------------------------------------
