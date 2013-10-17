
Float_t total(Float_t * array, unsigned n) {

    Float_t sum = 0;
    for (int i=0; i<n; i++) {
        sum += array[i]*array[i];
    }

    return TMath::Sqrt(sum);
}

int total_cross_section_syst() {

    Float_t b_plus[] = {1.4, 2, 2.0, 1.3, 0.8, 0.7, 0.3, 1.7, 2.9, 0.3, 0.7, 1.7, 5.4, 0.4, 1.8, 1.9};
    Float_t b_minus[] = {1.4, 2.0, 1.3, 0.8, 0.7, 0.3, 1.7, 2.9, 0.4, 0.4, 1.3, 4.2, 0.4, 0.9, 3.1, 2.1, 1.9};

    Float_t c_plus[] = {0.8, 1, 0.5, 1.2, 0.8, 0.9, 0.1, 1.8, 0.4, 1.5, 2.2, 0.5, 2, 1.0, 3.5, 1.9};
    Float_t c_minus[] = {0.8, 0.5, 1.2, 0.8, 0.9, 0.1, 1.8, 0.4, 1.0, 0.1, 1.7, 0.6, 2, 2.6, 1.9};

    cout << "beauty +" << total (b_plus, 16) << " -" << total (b_minus, 17) << endl;
    cout << "charm +" << total (c_plus, 16) << " -" << total (c_minus, 15) << endl;

    return 0;

}
