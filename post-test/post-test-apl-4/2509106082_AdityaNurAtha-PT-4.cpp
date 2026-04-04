#include <iostream>
using namespace std;

struct RekamMedis{
    string id;
    string nama;
    string tanggal;
    string diagnosis;
    string terapi;
    string catatan;
};

struct User{
    string username;
    string password;
    RekamMedis data[100];
    int jumlahData=0;
};

// ================= LOGIN =================
bool loginUser(User user){
    int percobaan=0;
    string username,password;

    while(percobaan<3){

        cout<<" LOGIN "<<endl;

        cout<<"Username: ";
        cin>>username;

        cout<<"Password: ";
        cin>>password;
        cin.ignore();

        if(username==user.username && password==user.password){
            cout<<"Login berhasil!"<<endl;
            return true;
        }
        else{
            percobaan++;
            cout<<"username/password salah ("<<percobaan<<"/3)"<<endl;
        }
    }

    cout<<"Program berhenti!"<<endl;
    return false;
}


// TAMBAH DATA
void tambahDataPointer(User *user){

    cout<<" CREATE DATA PASIEN "<<endl;

    if(user->jumlahData >= 100){
        cout<<"Data penuh!"<<endl;
        return;
    }

    int indexData = user->jumlahData;

    cin.ignore();

    cout<<"ID Pasien: ";
    getline(cin,user->data[indexData].id);

    cout<<"Nama Pasien: ";
    getline(cin,user->data[indexData].nama);

    cout<<"Tanggal Sesi: ";
    getline(cin,user->data[indexData].tanggal);

    cout<<"Diagnosis: ";
    getline(cin,user->data[indexData].diagnosis);

    cout<<"Terapi: ";
    getline(cin,user->data[indexData].terapi);

    cout<<"Catatan Evaluasi: ";
    getline(cin,user->data[indexData].catatan);

    user->jumlahData++;

    cout<<"Data berhasil ditambahkan"<<endl;
}

// LIHAT DATA
void lihatDataPointer(User *user){

    cout<<" DAFTAR REKAM MEDIS PASIEN "<<endl;

    if(user->jumlahData == 0){
        cout<<"Belum ada data"<<endl;
        return;
    }

    cout<<"---------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"No   \tID    \tNama  \tTanggal   \tDiagnosis     \tTerapi   \tCatatan"<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------"<<endl;

    for(int index=0; index<user->jumlahData; index++){

        cout<<index+1<<"\t"
            <<user->data[index].id<<"\t"
            <<user->data[index].nama<<"\t"
            <<user->data[index].tanggal<<"\t"
            <<user->data[index].diagnosis<<"\t"
            <<user->data[index].terapi<<"\t"
            <<user->data[index].catatan<<endl;
    }
}

// UBAH DATA
void ubahDataPointer(User *user){

    cout<<" UPDATE DATA PASIEN "<<endl;

    int nomorData;

    cout<<"Masukkan nomor data yang ingin diubah: ";
    cin>>nomorData;
    cin.ignore();

    nomorData--;

    if(nomorData>=0 && nomorData<user->jumlahData){

        cout<<"ID Pasien Baru: ";
        getline(cin,user->data[nomorData].id);

        cout<<"Nama Pasien Baru: ";
        getline(cin,user->data[nomorData].nama);

        cout<<"Tanggal Sesi Baru: ";
        getline(cin,user->data[nomorData].tanggal);

        cout<<"Diagnosis Baru: ";
        getline(cin,user->data[nomorData].diagnosis);

        cout<<"Terapi Baru: ";
        getline(cin,user->data[nomorData].terapi);

        cout<<"Catatan Perkembangan Baru: ";
        getline(cin,user->data[nomorData].catatan);

        cout<<"Data berhasil diperbarui"<<endl;
    }
    else{
        cout<<"Data tidak ditemukan"<<endl;
    }
}

// HAPUS DATA
void hapusDataPointer(User *user){

    cout<<" HAPUS DATA PASIEN "<<endl;

    int nomorData;

    cout<<"Masukkan nomor data yang ingin dihapus: ";
    cin>>nomorData;

    nomorData--;

    if(nomorData>=0 && nomorData<user->jumlahData){

        for(int index=nomorData; index<user->jumlahData-1; index++){
            user->data[index]=user->data[index+1];
        }

        user->jumlahData--;

        cout<<"Data berhasil dihapus"<<endl;
    }
    else{
        cout<<"Data tidak ditemukan"<<endl;
    }
}

// ================= MAIN =================
int main(){

    User user;

    user.username="Aditya";
    user.password="082";

    if(!loginUser(user)){
        return 0;
    }

    int pilihanMenu;

    do{

        cout<<endl;
        cout<<" MENU "<<endl;
        cout<<"1. Tambah Data"<<endl;
        cout<<"2. Lihat Data"<<endl;
        cout<<"3. Ubah Data"<<endl;
        cout<<"4. Hapus Data"<<endl;
        cout<<"5. Logout"<<endl;
        cout<<"Pilih: ";
        cin>>pilihanMenu;

        if(pilihanMenu==1){
            tambahDataPointer(&user);   
        }
        else if(pilihanMenu==2){
            lihatDataPointer(&user);
        }
        else if(pilihanMenu==3){
            ubahDataPointer(&user);
        }
        else if(pilihanMenu==4){
            hapusDataPointer(&user);
        }

    }while(pilihanMenu!=5);

    cout<<"Logout..."<<endl;
}