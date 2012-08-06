
Float_t total(Float_t * array, unsigned n) {

    Float_t sum = 0;
    for (int i=0; i<n; i++) {
        sum += array[i]*array[i];
    }

    return TMath::Sqrt(sum);
}

int total_cross_section_syst() {

    Float_t b_plus[]={1.4, 2, 2.8, 1.3, 0.8, 0.7, 3, 1.7, 1.8, 2};
    Float_t b_minus[]={1.4, 2.8, 1.3, 0.8, 0.7, 3, 1.3, 0.9, 3.1, 2.1, 2};

    Float_t c_plus[]={0.8, 1, 0.9, 1.2, 0.8, 0.9, 2, 2.2, 1.5, 2, 1.0, 3.5, 2};
    Float_t c_minus[]={0.8, 0.9, 1.2, 0.8, 0.9, 2, 1.7, 1.0, 2, 2.6, 2};

    cout << "beauty +" << total (b_plus, 10) << " -" << total (b_minus, 11) << endl;
    cout << "charm +" << total (c_plus, 13) << " -" << total (c_minus, 11) << endl;

    return 0;

}
