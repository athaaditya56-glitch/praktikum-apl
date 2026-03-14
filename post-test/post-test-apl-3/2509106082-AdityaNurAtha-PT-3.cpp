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

// fungsi
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
            cout<<"username/password salah brok !("<<percobaan<<"/3)"<<endl;        }
    }

    cout<<"Program berhenti!"<<endl;
    return false;
}

// prosedur
void tambahData(User &user){

    cout<<" CREATE DATA PASIEN "<<endl;

    int i=user.jumlahData;

    cin.ignore();

    cout<<"ID Pasien: ";
    getline(cin,user.data[i].id);

    cout<<"Nama Pasien: ";
    getline(cin,user.data[i].nama);

    cout<<"Tanggal Sesi: ";
    getline(cin,user.data[i].tanggal);

    cout<<"Diagnosis: ";
    getline(cin,user.data[i].diagnosis);

    cout<<"Terapi: ";
    getline(cin,user.data[i].terapi);

    cout<<"Catatan Evaluasi: ";
    getline(cin,user.data[i].catatan);

    user.jumlahData++;

    cout<<"Data rekam medis berhasil ditambahkan"<<endl;
}

// prosedur
void lihatData(User user){

    cout<<" DAFTAR REKAM MEDIS PASIEN "<<endl;

    cout<<"---------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"No   \tID    \tNama  \tTanggal   \tDiagnosis     \tTerapi   \tCatatan"<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------"<<endl;

    for(int i=0;i<user.jumlahData;i++){

        cout<<i+1<<"\t"
            <<user.data[i].id<<"\t"
            <<user.data[i].nama<<"\t"
            <<user.data[i].tanggal<<"\t"
            <<user.data[i].diagnosis<<"\t"
            <<user.data[i].terapi<<"\t"
            <<user.data[i].catatan<<endl;
    }
}

// prosedur
void ubahData(User &user){

    cout<<" UPDATE DATA PASIEN "<<endl;

    int ubah;

    cout<<"Masukkan nomor data yang ingin diubah: ";
    cin>>ubah;
    cin.ignore();

    ubah = ubah - 1;

    if(ubah>=0 && ubah<user.jumlahData){

        cout<<"ID Pasien Baru: ";
        getline(cin,user.data[ubah].id);

        cout<<"Nama Pasien Baru: ";
        getline(cin,user.data[ubah].nama);

        cout<<"Tanggal Sesi Baru: ";
        getline(cin,user.data[ubah].tanggal);

        cout<<"Diagnosis Baru: ";
        getline(cin,user.data[ubah].diagnosis);

        cout<<"Terapi Baru: ";
        getline(cin,user.data[ubah].terapi);

        cout<<"Catatan Perkembangan Baru: ";
        getline(cin,user.data[ubah].catatan);

        cout<<"Data berhasil diperbarui"<<endl;
    }

    else{
        cout<<"Data tidak ditemukan"<<endl;
    }
}

// prosedur
void hapusData(User &user){

    cout<<" HAPUS DATA PASIEN "<<endl;

    int hapus;

    cout<<"Masukkan nomor data yang ingin dihapus: ";
    cin>>hapus;
    cin.ignore();

    hapus = hapus - 1;

    if(hapus>=0 && hapus<user.jumlahData){

        for(int i=hapus;i<user.jumlahData-1;i++){
            user.data[i]=user.data[i+1];
        }

        user.jumlahData--;

        cout<<"Data berhasil dihapus"<<endl;
    }

    else{
        cout<<"Data tidak ditemukan"<<endl;
    }
}

int main(){

    User user;

    user.username="Aditya";
    user.password="082";

    if(!loginUser(user)){
        return 0;
    }

    int menu;

    do{

        cout<<endl;
        cout<<" MENU "<<endl;
        cout<<"1. Tambah Data"<<endl;
        cout<<"2. Lihat Data"<<endl;
        cout<<"3. Ubah Data"<<endl;
        cout<<"4. Hapus Data"<<endl;
        cout<<"5. Logout"<<endl;
        cout<<"Pilih: ";
        cin>>menu;

        if(menu==1){
            tambahData(user);
        }

        else if(menu==2){
            lihatData(user);
        }

        else if(menu==3){
            ubahData(user);
        }

        else if(menu==4){
            hapusData(user);
        }

    }while(menu!=5);

    cout<<"Logout..."<<endl;

}