export standard=`cat 2*r7_f7_m4.75 |gawk '($1~/Total/) {print $4}'`
cat *m4.5 *m5.0 *f1* *f2* *r1* *r2* | gawk '($1~/Total/) {if (ENVIRON["standard"]>$4) ssump+=(ENVIRON["standard"]-$4)^2 
                                                          if (ENVIRON["standard"]<$4) ssumm+=(ENVIRON["standard"]-$4)^2}
END{print ENVIRON["standard"] " + " sqrt(ssump) " - " sqrt(ssumm)}'

export standard=`cat 2*r7_f7_m4.75 |gawk '($1~/muon/) {print $4}'`
cat *m4.5 *m5.0 *f1* *f2* *r1* *r2* | gawk '($1~/muon/) {if (ENVIRON["standard"]<$4) ssump+=(ENVIRON["standard"]-$4)^2 
                                                         if (ENVIRON["standard"]>$4) ssumm+=(ENVIRON["standard"]-$4)^2}
END{print ENVIRON["standard"] " + " sqrt(ssump) " - " sqrt(ssumm)"  upper value:"ENVIRON["standard"]+sqrt(ssump) "  lower value:" ENVIRON["standard"]-sqrt(ssumm)  }'
