#include "../include/Texture.h"
#include "../include/Printer.h"

#include <random>

Texture::Texture(std::vector<std::vector<int> > R,
		std::vector<std::vector<int> > G,
		std::vector<std::vector<int> > B,
		std::vector<std::vector<int> > A, int sizeX, int sizeY){
	this->R=R;
	this->G=G;
	this->B=B;
	this->A=A;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

Texture Texture::createSingleColorTexture(int R, int G, int B, int A){
	std::vector<std::vector<int> > vecR(1);
	vecR[0].push_back(R);
	std::vector<std::vector<int> > vecG(1);
	vecG[0].push_back(G);
	std::vector<std::vector<int> > vecB(1);
	vecB[0].push_back(B);
	std::vector<std::vector<int> > vecA(1);
	vecA[0].push_back(A);

	return Texture(vecR, vecG, vecB, vecA, 1, 1);
}

class truncated_normal_distribution:public std::normal_distribution<double>{
	public:
	truncated_normal_distribution(double mean = 0.0, double stddev = 1.0):std::normal_distribution<double>(mean,stddev){};
	double operator()(std::default_random_engine& g);
	private:
	static const int max = 255;
	static const int min = 0;
};

double truncated_normal_distribution::operator()(std::default_random_engine& g){
	double result = std::normal_distribution<double>::operator()(g);
	if (result > 255)
		return 255;
	else if (result < 0)
		return 0;
	else	return result;
}

Texture Texture::createGrainedColorTexture(int R,int G, int B, int A, double grainAmount){
	std::default_random_engine generator;

	truncated_normal_distribution Rdist((double)R,grainAmount);
	truncated_normal_distribution Gdist((double)G,grainAmount);
	truncated_normal_distribution Bdist((double)B,grainAmount);
	truncated_normal_distribution Adist((double)A,grainAmount);

	if (grainAmount<0)
		grainAmount = -grainAmount;

	int size = 1+grainAmount*2;
	std::vector<std::vector<int> > vecR(size);
	std::vector<std::vector<int> > vecG(size);
	std::vector<std::vector<int> > vecB(size);
	std::vector<std::vector<int> > vecA(size);
	for (int i=0;i<size;i++){
		vecR[i]=std::vector<int>(size);
		vecG[i]=std::vector<int>(size);
		vecB[i]=std::vector<int>(size);
		vecA[i]=std::vector<int>(size);
		for (int j=0;j<size;j++){
			vecR[i][j]=Rdist(generator);
			vecG[i][j]=Gdist(generator);
			vecB[i][j]=Bdist(generator);
			vecA[i][j]=Adist(generator);
		}
	}
	return Texture(vecR,vecG,vecB,vecA,size,size);	
}

Texture Texture::fromStream(std::istream& inputfile){
	int M,N;
	inputfile>>M;
	inputfile>>N;
	std::vector<std::vector<int> > vecR(M);
	std::vector<std::vector<int> > vecG(M);
	std::vector<std::vector<int> > vecB(M);
	std::vector<std::vector<int> > vecA(M);
	for (int i=0;i<M;i++){
		vecR[i].resize(N);
		vecG[i].resize(N);
		vecB[i].resize(N);
		vecA[i].resize(N);
		for (int j=0;j<N;j++){
			inputfile>>vecR[i][j];
			inputfile>>vecG[i][j];
			inputfile>>vecB[i][j];
			inputfile>>vecA[i][j];
		}
	}
	return Texture(vecR, vecG, vecB, vecA, N, M);
}

void Texture::draw(int x,int y){
	if (sizeX<=0 && sizeY<=0) return;
	if (x<0 || y<0) return;
	int j = x%sizeX;
	int i = y%sizeY;

	Printer::drawPix(x,y,R[i][j],G[i][j],B[i][j],A[i][j]);
}

	//transformasi
Texture Texture::scaleResult(float xScale, float yScale){
	int _sizeY = sizeY*yScale;
	int _sizeX = sizeX*yScale;
	if (_sizeY==0)
		_sizeY=1;
	if (_sizeX==0)
		_sizeX=1;
	std::vector<std::vector<int> > _R(_sizeY);
	std::vector<std::vector<int> > _G(_sizeY);
	std::vector<std::vector<int> > _B(_sizeY);
	std::vector<std::vector<int> > _A(_sizeY);
	for (int i=0;i<_sizeY;i++){
		_R[i].resize(_sizeX);
		_G[i].resize(_sizeX);
		_B[i].resize(_sizeX);
		_A[i].resize(_sizeX);
		for (int j=0;j<_sizeX;j++){
			int refi=i/yScale;
			int refj=j/xScale;
			_R[i][j]=R[refi][refj];
			_G[i][j]=G[refi][refj];
			_B[i][j]=B[refi][refj];
			_A[i][j]=A[refi][refj];
		}
	}
	return Texture(_R,_G,_B,_A,sizeX,sizeY);
}
Texture Texture::translateResult(int deltaX, int deltaY){
	std::vector<std::vector<int> > _R(sizeY);
	std::vector<std::vector<int> > _G(sizeY);
	std::vector<std::vector<int> > _B(sizeY);
	std::vector<std::vector<int> > _A(sizeY);
	for (int i=0;i<sizeY;i++){
		_R[i].resize(sizeX);
		_G[i].resize(sizeX);
		_B[i].resize(sizeX);
		_A[i].resize(sizeX);
		for (int j=0;j<sizeX;j++){
			int refi=((i-deltaY)%sizeY+sizeY)%sizeY;
			int refj=((j-deltaX)%sizeX+sizeX)%sizeX;
			_R[i][j]=R[refi][refj];
			_G[i][j]=G[refi][refj];
			_B[i][j]=B[refi][refj];
			_A[i][j]=A[refi][refj];
		}
	}
	return Texture(_R,_G,_B,_A,sizeX,sizeY);
}
