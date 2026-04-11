#include <iostream>
#include <cctype>
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

int ambilAngka(string id){
    int angka = 0;
    for(int i=0;i<id.length();i++){
        if(isdigit(id[i])){
            angka = angka * 10 + (id[i]-'0');
        }
    }
    return angka;
}

// ================= LOGIN =================
bool loginUser(User &user){
    int percobaan=0;
    string username,password;

    while(percobaan<3){
        cout<<" LOGIN "<<endl;

        cout<<"Username: ";
        cin>>username;

        cout<<"Password: ";
        cin>>password;

        if(username==user.username && password==user.password){
            cout<<"Login berhasil!"<<endl;
            return true;
        }
        else{
            percobaan++;
            cout<<"Username/password salah ("<<percobaan<<"/3)"<<endl;
        }
    }

    cout<<"Program berhenti!"<<endl;
    return false;
}

// ================= TAMBAH DATA =================
void tambahData(User &user){

    cout<<" CREATE DATA PASIEN "<<endl;

    if(user.jumlahData >= 100){
        cout<<"Data penuh!"<<endl;
        return;
    }

    int i = user.jumlahData;
    cin.ignore();

    cout<<"ID Pasien: ";
    getline(cin,user.data[i].id);

    cout<<"Nama Pasien: ";
    getline(cin,user.data[i].nama);

    cout<<"Tanggal (YYYY-MM-DD): ";
    getline(cin,user.data[i].tanggal);

    cout<<"Diagnosis: ";
    getline(cin,user.data[i].diagnosis);

    cout<<"Terapi: ";
    getline(cin,user.data[i].terapi);

    cout<<"Catatan: ";
    getline(cin,user.data[i].catatan);

    user.jumlahData++;

    cout<<"Data berhasil ditambahkan"<<endl;
}

// ================= LIHAT DATA =================
void lihatData(User &user){

    cout<<" DAFTAR REKAM MEDIS "<<endl;

    if(user.jumlahData==0){
        cout<<"Belum ada data"<<endl;
        return;
    }

    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"No\tID\tNama\t\tTanggal\t\tDiagnosis\tTerapi\t\tCatatan"<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;

    for(int i=0;i<user.jumlahData;i++){
        cout<<i+1<<"\t"
            <<user.data[i].id<<"\t"
            <<user.data[i].nama<<"\t\t"
            <<user.data[i].tanggal<<"\t"
            <<user.data[i].diagnosis<<"\t\t"
            <<user.data[i].terapi<<"\t\t"
            <<user.data[i].catatan<<endl;
    }
}

// ================= UBAH DATA =================
void ubahData(User &user){

    int n;
    cout<<"Nomor data: ";
    cin>>n;
    cin.ignore();

    n--;

    if(n>=0 && n<user.jumlahData){

        cout<<"ID baru: ";
        getline(cin,user.data[n].id);

        cout<<"Nama baru: ";
        getline(cin,user.data[n].nama);

        cout<<"Tanggal baru: ";
        getline(cin,user.data[n].tanggal);

        cout<<"Diagnosis baru: ";
        getline(cin,user.data[n].diagnosis);

        cout<<"Terapi baru: ";
        getline(cin,user.data[n].terapi);

        cout<<"Catatan baru: ";
        getline(cin,user.data[n].catatan);

        cout<<"Data berhasil diubah"<<endl;
    }
    else{
        cout<<"Data tidak ditemukan"<<endl;
    }
}

// ================= HAPUS DATA =================
void hapusData(User *user){

    int n;
    cout<<"Nomor data: ";
    cin>>n;

    n--;

    if(n>=0 && n<user->jumlahData){

        for(int i=n;i<user->jumlahData-1;i++){
            user->data[i]=user->data[i+1];
        }

        user->jumlahData--;

        cout<<"Data berhasil dihapus"<<endl;
    }
    else{
        cout<<"Data tidak ditemukan"<<endl;
    }
}

//  SORTING

// QUICK SORT (Nama DESC)
int partitionNama(User &user,int low,int high){
    string pivot = user.data[high].nama;
    int i=low-1;

    for(int j=low;j<high;j++){
        if(user.data[j].nama > pivot){
            i++;
            swap(user.data[i],user.data[j]);
        }
    }

    swap(user.data[i+1],user.data[high]);
    return i+1;
}

void quickSortNama(User &user,int low,int high){
    if(low<high){
        int pi = partitionNama(user,low,high);
        quickSortNama(user,low,pi-1);
        quickSortNama(user,pi+1,high);
    }
}

// SELECTION SORT (ID ASC)
void selectionSortID(User &user){
    for(int i=0;i<user.jumlahData-1;i++){
        int min=i;

        for(int j=i+1;j<user.jumlahData;j++){
            if(ambilAngka(user.data[j].id) < ambilAngka(user.data[min].id)){
                min=j;
            }
        }

        swap(user.data[i],user.data[min]);
    }

    cout<<"Sorting ID ASC berhasil"<<endl;
}

// INSERTION SORT (Tanggal ASC)
void insertionSortTanggal(User &user){
    for(int i=1;i<user.jumlahData;i++){
        RekamMedis key = user.data[i];
        int j=i-1;

        while(j>=0 && user.data[j].tanggal > key.tanggal){
            user.data[j+1]=user.data[j];
            j--;
        }

        user.data[j+1]=key;
    }

    cout<<"Sorting tanggal ASC berhasil"<<endl;
}

// ================= MAIN =================
int main(){

    User user;
    user.username="Aditya";
    user.password="082";

    if(!loginUser(user)) return 0;

    int pilih;

    do{
        cout<<"\nMENU\n";
        cout<<"1. Tambah\n";
        cout<<"2. Lihat\n";
        cout<<"3. Ubah\n";
        cout<<"4. Hapus\n";
        cout<<"5. Sort Nama \n";
        cout<<"6. Sort ID \n";
        cout<<"7. Sort Tanggal \n";
        cout<<"8. Logout\n";
        cout<<"Pilih: ";
        cin>>pilih;

        if(pilih==1) tambahData(user);
        else if(pilih==2) lihatData(user);
        else if(pilih==3) ubahData(user);
        else if(pilih==4) hapusData(&user);

        else if(pilih==5){
            if(user.jumlahData==0){
                cout<<"Tidak ada data untuk disorting"<<endl;
            } else {
                quickSortNama(user,0,user.jumlahData-1);
                cout<<"Sorting nama DESC berhasil"<<endl;
            }
        }

        else if(pilih==6){
            if(user.jumlahData==0){
                cout<<"Tidak ada data untuk disorting"<<endl;
            } else {
                selectionSortID(user);
            }
        }

        else if(pilih==7){
            if(user.jumlahData==0){
                cout<<"Tidak ada data untuk disorting"<<endl;
            } else {
                insertionSortTanggal(user);
            }
        }

    }while(pilih!=8);

    cout<<"Logout..."<<endl;
}