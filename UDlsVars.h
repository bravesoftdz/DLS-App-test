// ---------------------------------------------------------------------------

#ifndef UDlsVarsH
#define UDlsVarsH
// ---------------------------------------------------------------------------
#include "UMyInfernalType.h"
#include <vector>
#include "Device.h"
#include "UProgectData.h"
#include "VirtualTrees.hpp"
#include "UTAdjustAngleAperForm.h"
#include "MainFormUnit.h"

using namespace std;

typedef void(__stdcall*pDLSCumulants)(double*p, double*t, double*w, int n,
	double&a0, double&a1, double&a2);
typedef void(__stdcall*pDLSContin)(double*t, double*y, double*s, double*g0,
	int _ns, int _nt, double _alpha, double _eta);
typedef void(__stdcall*pDLSLogSpace)(double d1, double d2, int n, double*p);
typedef void(__stdcall*pDimMatrix)(float*a, int n, int m);
typedef void(__stdcall*pDelMatrix)(float*a, int n, int m);
typedef void(__stdcall*pLinEq)(float*a, float*b, int lb, int ub, float*det);

typedef double(__stdcall*pIntPower)(double x, int n);
typedef void(__stdcall*pLinApprox)(double*x, double*y, int n, double*a,
	double*b);

typedef void(__stdcall*pDimVector)(void*a, int n);
typedef void(__stdcall*pDelVector)(void*a, int n);
typedef double(*pExp2)(double x);


class Seq_Exception : public Exception
{
public:
	inline __fastcall Seq_Exception(const System::UnicodeString Msg): Exception(Msg) {}
	inline __fastcall virtual ~Seq_Exception(void){};
};

enum dls_mode {acf_ = 0, rec_, none_};


struct TGrad {
	UnicodeString a, b, angle;
};

struct TAcfParams {
	bool lfd, feu;
	int vybr; // �������
	int zashk; // �������
	int nRawData; // ���������� ����� �������� ������
	int _p;
	int n_min, _n_min;
	int n_block;
	int Gauss_w;
	int n_avt; // ���������� ����� ���
	int _m;
	int n0;
	int _s;
	double t_block;
	int n_mean;
	double cut; // ������ ������� ������� ����� ��� ��� ������� �� ������ ���������� ��� contin
	int cut_after; // ������� ������� ������� ����� ��� ��� ������� �� ������ ���������� ��� contin
	bool right_boundary; // �������������� ����� ������ �������
	int ns; // ���������� ����� ����������� ������ contin
	double _time;
	int dt0; // ����� ����� �������
	double PI;
	double x_pcs;
	double n, lambda, theta, eta, Kb, T;
	double alpha; // �������� ������������� ������ contin
	double t_discr;
	double angle_step; // ������� ���� ������ ���� �������� ���������
	double angle_init; // �������� �� ��������� ����
	int _vybr; // ����� ������������ ��������
	double cont_low; // ������ ������� ��������� ������� ������������� ������
	double cont_high; // ������� ������� ��������� ������� ������������� ������
	double cont_low_graph; // ������ ������� ������ �� ������
	double cont_high_graph; // ������� ������� ������ �� ������
	int grad_count, grad_n;
	vector<TGrad>grad;
	bool cont_hist;
	double a0, a1, a2;
	double Curr_T;

	int Time_discr;
	bool Multi_Angle;
	char Initial_Angle;
	float Angle_Shift;
	int num_Angles;
	int n_seq;
	int seq_time;
	int n_rec;
	int Rec_time;
	bool DoAcf;
	bool DoMean;
	UnicodeString Name_Spec;
	UnicodeString Name_Sol;
	UnicodeString Save_Dir;
	UnicodeString File_Name;

	char Prism;
	char Aperture;
	char Polar;

    int Intensity;
	bool Kinetics;

	TAcfParams();
};



struct TReportData {
	int num;
	UnicodeString Name;
	double pcs;
	double pi;
	double angle;
	double rms;
	double a1;
	double a2;
	double t;
};

enum TAquireMode {from_device = 0, from_hdd};

struct TSeqThreadParams
{
	UnicodeString Save_Dir, File_Name;

	float ScatAngle;
	bool DoMean, DoAcf, Multi_Angle;
	int n_rec, n_seq;
	int num_rec, num_seq;
	char Initial_Angle;
	TAquireMode mode;
};

extern void *CaptureDone, *AcfDone;
extern Device device;
extern TMyInfernalType RawData, RawData_t, acf, acf_t, cum, cum_t, contin_g,
contin_s;
extern TAcfParams AcfParams;
extern TReportData ReportData;
extern TDataParams DataParams;

void ProcessAcfData(WORD * p, int n0, double t);
void SaveAcf2Txt(UnicodeString s);
void SaveAcf2Crv(UnicodeString s);
void SaveAcf2Tdf(UnicodeString s);
void SaveAcf2Tdf(UnicodeString s, TDataParams DataParams_);
void OpenTdf(UnicodeString s);
double CheckString(UnicodeString s);
void CreateCrv(double*p, double*t, int w, UnicodeString s);
void LoadCrv(TMyInfernalType & p, TMyInfernalType & t, UnicodeString s);
void Interp(double*p, int n, double tin, double dt);
double NuttallWin(double x, double x0, double w);
double FormulaPuazeilia(double t);
bool OptionsFormExecute();
bool OpenProject(UnicodeString Name, TProjectData &pd);
void SaveProject(TProjectData *pd_);
void ExtractDataParams(UnicodeString Name, TDataParams *params);
void ProcessData(dls_mode mode, UnicodeString Name, int seq_num, int rec_num, UnicodeString data_Name = "");
void ProcessData(TProjectData::TVtPD *d);
void OpenData(WORD **data, int &n, UnicodeString Name);
double GetTime_Discr(int i);
void AddToVt( TProjectData &pd_ , TVirtualStringTree *vt );
void UpdateVt( TVirtualStringTree *vt );
void RegisterExt();
bool CheckExistProject(UnicodeString FileName);
void getRateGraph(WORD *Data, int n0, std::vector<double> &rate, std::vector<double> &time);


typedef struct ThreadData
{
	char index;
	int value;
} *PThreadData;


class TThreadParams: public TThread
{
protected:
	void __fastcall Execute()
	{
		switch (mode) {
			case 0: {
				void *q = CreateEvent(NULL, true, false, NULL);
				Status status;
				status.byte = 0;
				device.SetAngle(AcfParams.Initial_Angle);
				do {
					WaitForSingleObject(q, 100);
					device.GetStatus(status);
				}
				while (!status.bits.goniometer);

				status.byte = 0;
				device.SetAperture(AcfParams.Aperture);
				do {
					WaitForSingleObject(q, 100);
					device.GetStatus(status);
				}
				while (!status.bits.aperture);
				CloseHandle(q);
				break;
			}
			case 1: {
				device.WriteData(AcfParams.Initial_Angle*2, value);
				void *q = CreateEvent(NULL, true, false, NULL);
				Status status;
				status.byte = 0;
				//device.SetAngle(AcfParams.Initial_Angle);
				do {
					WaitForSingleObject(q, 100);
					device.GetStatus(status);
				}
				while (!status.bits.goniometer);
				CloseHandle(q);
				break;
			}
			case 2: {
				device.WriteData(24, value);
				void *q = CreateEvent(NULL, true, false, NULL);
				Status status;
				status.byte = 0;
				//device.SetAperture(AcfParams.Aperture);
				do {
					WaitForSingleObject(q, 100);
					device.GetStatus(status);
				}
				while (!status.bits.aperture);
				CloseHandle(q);
				break;
			}

		}


		/*
		if (d->index <= 22) {
			device.WriteData(d->index, d->value);
			void *q = CreateEvent(NULL, true, false, NULL);
			Status status;
			status.byte = 0;
			device.SetAngle(d->index);
			do {
				WaitForSingleObject(q, 100);
				device.GetStatus(status);
			}
			while (status.bits.goniometer);
			CloseHandle(q);
		}

		if (d->index == 24) {
			device.WriteData(d->index, d->value);
			void *q = CreateEvent(NULL, true, false, NULL);
			Status status;
			status.byte = 0;
			device.SetAperture(d->index);
			do {
				WaitForSingleObject(q, 100);
				device.GetStatus(status);
			}
			while (status.bits.aperture);
			CloseHandle(q);
		}
		*/

		SetEvent(wait_event);

		if (Draw)
        	Synchronize(Draw);


	}

public:

	//char index;
	int value;
	int mm;
	int mode;
	void *wait_event;
	TThreadMethod Draw;
	/*
	void __fastcall Draw2()
	{
		switch (mm) {
			case 0:
				MainForm->StartMonitoring();
				AdjustAngleAperForm->Show();
			break;

		}
	}
	*/
	__fastcall TThreadParams(bool CreateSuspended) : TThread(CreateSuspended), mm(-1), Draw(NULL) { };
};



// extern void __declspec(dllimport) DLSCumulants(double *p, double *t, double *w, int n, double &a0,  double &a1, double &a2);

#endif
