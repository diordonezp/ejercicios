#include<iostream>
#include<vector>

void print(std::vector<int> a,std::vector<int> b,std::vector<int> c);
void play(int d,std::vector<int> &i,std::vector<int> &f);
void play1(int d, std::vector<int> &i,std::vector<int> &f,std::vector<int> &aux);
bool test(int d,std::vector<int> i,std::vector<int> f);
void game(std::vector<int> &a,std::vector<int> &b,std::vector<int> &c);

int main(void)
{
  int N=5;
  std::vector<int> A(N);
  std::vector<int> B(N);
  std::vector<int> C(N);

  for(int i=0;i<N;i++){
    A[i]=i+1;
  }
  for(int i=0;i<N;i++){
    B[i]=0;
  }
  for(int i=0;i<N;i++){
    C[i]=0;
  }

  game(A,B,C);  

  return 0;
}

void print(std::vector<int> a,std::vector<int> b,std::vector<int> c)
{
  for(int i=0;i<a.size();i++){
    std::cout<<a[i]<<"  "<<b[i]<<"  "<<c[i]<<"\n";
  }
}

//la primera función se basa en la jugada fundamental de mover un disco en la posición d de la columna i a la columna f, si este movimiento es válido
void play(int d,std::vector<int> &i,std::vector<int> &f)
{
  int aux=i[d];

  if(d!=0 && i[d-1]!=0){
    std::cout<<"INVALID MOVE: DISC ABOVE.\n";
  }
  
  if(i[d]==0){
    std::cout<<"INVALID MOVE: NO DISC TO PLAY.\n";
  }

  else{    
    for(int j=0;j<f.size();j++){
      if(f[j+1]<aux && f[j+1]!=0){
	std::cout<<"INVALID MOVE: DISC BELOW SMALLER.\n";
	break;
      }
      if(f[j+1]!=0){
	f[j]=aux;
	i[d]=0;
	break;
      }
    }
    if(f[f.size()-1]==0){
      f[f.size()-1]=aux;
      i[d]=0;
    }
  }
}

//la recurrencia para que un disco que no se puede mover en una sola jugada se pueda mover: para mover el disco d de i a f, mover el disco d-1 de i a aux.
void play1(int d, std::vector<int> &i,std::vector<int> &f,std::vector<int> &aux)
{
  if(d==0 || i[d-1]==0){
    if(test(d,i,f)==0){
      int resid=0;
      for(int j=0;j<f.size();j++){
	if(f[j]!=0){
	  resid=j;
	  break;
	}
      }
      play1(resid,f,aux,i);
    }
    else{
      play(d,i,f);
    }
  }

  else{
    play1(d-1,i,aux,f);
  }
}

//para revisar si después de completar la recurrencia es posible que el disco d si se mueva a la columna f, pues la recurrencia va a mover los discos anteriores a d a las columnas f y aux, y hay que reacomodarlos
bool test(int d,std::vector<int> i,std::vector<int> f)
{
  bool res=true;
  int c_f=i[d];

  for(int j=0;j<f.size();j++){
    if(f[j]!=0){
      c_f=f[j];
      break;
    }
  }
  if(i[d]>c_f){
    res=false;
  }
  return res;
}

//el juego debe usar las recurrencias, los test, y las jugadas para completar el hanoi de manera automática. La lógica de la recurrencia se pierde cuando encima del 4 disco queda el 1 disco, hay que cambiar la lógica despúes de ese movimiento
void game(std::vector<int> &A,std::vector<int> &B,std::vector<int> &C)
{
  int N=A.size();
  print(A,B,C);
  std::cout<<"\n";
  for(;;){
    if(A[N-1]!=0 && A[2]!=1){
      play1(N-1,A,C,B);
      print(A,B,C);
      std::cout<<"\n";
    }
    else break;
  }
  /*if(N>3){
    if(B[N-1]<C[N-1]){
      play(N-1,B,C);
      play(2,A,C);
    }
    else if(B[N-1]>C[N-1]){
      play(N-1,C,B);
      play(2,A,B);
    }
    print(A,B,C);
    }*/
}
