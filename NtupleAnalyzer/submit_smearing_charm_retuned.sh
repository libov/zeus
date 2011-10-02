# default smearing
#./submit_analysis -b full.forCHARM -v 2.22.0 --gaus1prob 0.05 --gaus1width 1.8 --gaus2prob 0.01 --gaus2width 2.3 --expprob 0.1 --expcoeff 5
# retuned smearing; note wrong version
#./submit_analysis -b full.forCHARM -v 2.21.1 --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.002 --gaus2width 7 --expprob 0

# variation of retuned smearing

# variation of 1st gaussian
./submit_analysis -b full.forCHARM -v 2.22.2  --gaus1prob 0.03 --gaus1width 1.6 --gaus2prob 0.002  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.3  --gaus1prob 0.05 --gaus1width 1.6 --gaus2prob 0.002  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.4  --gaus1prob 0.06 --gaus1width 1.6 --gaus2prob 0.002  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.5  --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.002  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.6  --gaus1prob 0.08 --gaus1width 1.6 --gaus2prob 0.002  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.7  --gaus1prob 0.09 --gaus1width 1.6 --gaus2prob 0.002  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.8  --gaus1prob 0.11 --gaus1width 1.6 --gaus2prob 0.002  --gaus2width 7

# variation of 2nd gaussian
./submit_analysis -b full.forCHARM -v 2.22.9  --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.000  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.10 --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.0005 --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.11 --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.001  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.12 --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.0015 --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.13 --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.002  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.14 --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.0025 --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.15 --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.003  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.16 --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.004  --gaus2width 7
./submit_analysis -b full.forCHARM -v 2.22.17 --gaus1prob 0.07 --gaus1width 1.6 --gaus2prob 0.005  --gaus2width 7