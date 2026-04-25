void cariNama(User *user){
    try{
        if(user->jumlahData==0){
            throw runtime_error("Data kosong");
        }

        string key;
        cin.ignore();
        cout<<"Masukkan nama: ";
        getline(cin,key);

        int hasil = linearSearchNama(user,key);

        if(hasil!=-1){
            cout<<"Data ditemukan:\n";
            cout<<user->data[hasil].id<<" - "<<user->data[hasil].nama<<endl;
        } else {
            throw runtime_error("Data tidak ditemukan");
        }
    }
    catch(exception &e){
        cout<<e.what()<<endl;
    }
}