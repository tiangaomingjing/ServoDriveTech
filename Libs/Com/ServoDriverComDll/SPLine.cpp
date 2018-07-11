#include "stdafx.h"
#include "SPLine.h"
#include "BaseReturn_def.h"

CSPLine::CSPLine()
{
}


CSPLine::~CSPLine()
{
}

//-------------------------------------------------------------------------------------------------
// ��˹����Ԫ��ȥ�������Է�����
//-------------------------------------------------------------------------------------------------
// n		���̸���
// pA		������ϵ����n�У�n+1�� 
// pResult	������Ľ�
//-------------------------------------------------------------------------------------------------

short CSPLine::Gauss(long n, double *pA, double *pResult)
{
	long i, j, k, maxLine;
	double maxData, temp, coef;

	// ��Ԫ
	for (i = 1; i < n; ++i)												// ������
	{
		maxLine = i - 1;												// Ѱ������Ԫ
		maxData = pA[(i - 1)*(n + 1) + (i - 1)];
		for (j = i; j<n; ++j)
		{
			if (pA[j*(n + 1) + (i - 1)] > maxData)
			{
				maxLine = j;
				maxData = pA[j*(n + 1) + (i - 1)];
			}
		}

		if (0 == maxData)
		{
			return CMD_ERROR_PARAMETER;
		}

		if (maxLine != i - 1)										// ������
		{
			for (j = i - 1; j <= n; ++j)
			{
				temp = pA[(i - 1)*(n + 1) + j];
				pA[(i - 1)*(n + 1) + j] = pA[maxLine*(n + 1) + j];
				pA[maxLine*(n + 1) + j] = temp;
			}
		}

		for (j = i; j < n; ++j)											// ������
		{
			for (k = i; k <= n; ++k)										// ����Ԫ��
			{
				coef = pA[j*(n + 1) + (i - 1)] / pA[(i - 1)*(n + 1) + (i - 1)];
				pA[j*(n + 1) + k] -= coef * pA[(i - 1)*(n + 1) + k];
			}
		}
	}

	// �ش�
	for (i = n - 1; i >= 0; --i)												// ���������
	{
		pResult[i] = pA[i*(n + 1) + n];
		for (j = n - 1; j > i; --j)											// �������Ԫ��
		{
			pResult[i] -= pResult[j] * pA[i*(n + 1) + j];
		}

		if (0 == pA[i*(n + 1) + i])
		{
			return 1;
		}

		pResult[i] /= pA[i*(n + 1) + i];
	}

	return CMD_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
// 3��������ֵ��ָ���߽��һ�׵���
//-------------------------------------------------------------------------------------------------
// y = yn + an(x-xn) + bn(x-xn)^2 + cn(x-xn)^3
//-------------------------------------------------------------------------------------------------
// n			����
// pX,pY		�ڵ�����
// dy0,dyn		�����յ��һ�׵���
// pG			��������3��������ϵ��a
// pMu			��������3��������ϵ��b
// pLambda		��������3��������ϵ��c
//-------------------------------------------------------------------------------------------------

short CSPLine::SplineComplete(long n, const double *pX, const double *pY, double *pG, double *pMu, double *pLambda, double dy0, double dyn)
{
	double h, hi, s, b, c;
	long i;

	if (n < 2)
	{
		return CMD_ERROR_PARAMETER;
	}

	// pX���뵥����
	for (i = 0; i < n - 1; ++i)
	{
		if (pX[i + 1] <= pX[i])
		{
			return CMD_ERROR_PARAMETER;
		}
	}

	if (2 == n)
	{
		goto lbl_spline_first_get_abc;
	}

	// �����м�n-2����[1..n-2]��lambda, mu, g,
	h = pX[1] - pX[0];

	for (i = 1; i <= (n - 2); ++i)
	{
		hi = pX[i + 1] - pX[i];
		pLambda[i] = hi / (hi + h);
		pMu[i] = 1 - pLambda[i];
		pG[i] = 3 * (pMu[i] * (pY[i + 1] - pY[i]) / hi + pLambda[i] * (pY[i] - pY[i - 1]) / h);

		h = hi;
	}

	pG[1] = pG[1] - pLambda[1] * dy0;
	pG[(n - 2)] = pG[(n - 2)] - pMu[(n - 2)] * dyn;

	// �����м�n-2����[1..n-2]���ٶ�, �������洢��pG��
	pMu[1] = pMu[1] / 2;
	pG[1] = pG[1] / 2;

	if (3 == n)
	{
		goto lbl_spline_first_get_abc;
	}

	// ��Ԫ
	for (i = 2; i <= (n - 2) - 1; ++i)
	{
		s = 2 - pLambda[i] * pMu[i - 1];
		pMu[i] = pMu[i] / s;
		pG[i] = (pG[i] - pLambda[i] * pG[i - 1]) / s;
	}

	// ����m(n-2)
	s = 2 - pLambda[(n - 2)] * pMu[(n - 2) - 1];
	pG[(n - 2)] = (pG[(n - 2)] - pLambda[(n - 2)] * pG[(n - 2) - 1]) / s;

	// �ش�
	for (i = (n - 2) - 1; i >= 1; --i)
	{
		pG[i] = pG[i] - pMu[i] * pG[i + 1];
	}

lbl_spline_first_get_abc:

	pG[0] = dy0;
	pG[n - 1] = dyn;

	// ������ε�a,b,c
	for (i = 0; i <= (n - 2); ++i)
	{
		hi = pX[i + 1] - pX[i];
		b = (3 * (pY[i + 1] - pY[i]) / hi - pG[i + 1] - 2 * pG[i]) / hi;
		c = (pG[i + 1] + pG[i] - 2 * (pY[i + 1] - pY[i]) / hi) / (hi*hi);

		pMu[i] = b;
		pLambda[i] = c;
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------
// 3��������ֵ�����ں���
//-------------------------------------------------------------------------------------------------
// y = yn + an(x-xn) + bn(x-xn)^2 + cn(x-xn)^3
//-------------------------------------------------------------------------------------------------
// n			����
// pX,pY		�ڵ�����
// pLambda		��������3��������ϵ��c
// pMu			��������3��������ϵ��b
// pG			��������3��������ϵ��a
//-------------------------------------------------------------------------------------------------

short CSPLine::SplinePeriodic(long n, const double *pX, const double *pY, double *pG, double *pMu, double *pLambda)
{
	double h, hi, s, last, b, c;
	double coef[3][4];
	long i;
	short rtn;

	if (n < 2)
	{
		return CMD_ERROR_PARAMETER;
	}

	// pX���뵥����
	for (i = 0; i < n - 1; ++i)
	{
		if (pX[i + 1] <= pX[i])
		{
			return CMD_ERROR_PARAMETER;
		}
	}

	// pY[0] = pY[n-1]
	if (pY[0] != pY[n - 1])
	{
		return CMD_ERROR_PARAMETER;
	}

	if (2 == n)
	{
		pG[0] = pG[1] = 0;
		goto lbl_spline_periodic_get_abc;
	}

	// �����м�n-1����[1..n-1]��lambda, mu, g
	h = pX[1] - pX[0];

	for (i = 1; i <= (n - 2); ++i)
	{
		hi = pX[i + 1] - pX[i];
		pLambda[i] = hi / (hi + h);
		pMu[i] = 1 - pLambda[i];
		pG[i] = 3 * (pMu[i] * (pY[i + 1] - pY[i]) / hi + pLambda[i] * (pY[i] - pY[i - 1]) / h);

		h = hi;
	}

	// �����յ��lambda,mu,g
	h = pX[1] - pX[0];
	hi = pX[(n - 1)] - pX[(n - 1) - 1];

	// lambda(n)=h(0)/(h(0)+h(n-1))
	pLambda[(n - 1)] = h / (h + hi);

	// m(n)=h(n-1)/(h(0)+h(n-1))
	pMu[(n - 1)] = 1 - pLambda[(n - 1)];

	// g(n)=3*( mu(n)*(y(1)-y(0))/(x(1)-x(0)) + lambda(n)*(y(n)-y(n-1))/(x(n)-x(n-1)) )
	pG[(n - 1)] = 3 * (pMu[(n - 1)] * (pY[1] - pY[0]) / h + pLambda[(n - 1)] * (pY[(n - 1)] - pY[(n - 1) - 1]) / hi);

	if (3 == n)
	{
		pG[0] = (2 * pG[2] - pG[1]) / 3;
		pG[1] = (2 * pG[1] - pG[2]) / 3;
		pG[2] = pG[0];
		goto lbl_spline_periodic_get_abc;
	}

	// �����м�n-1����[1..n-2]�ĵ���, �������洢��pG��
	pMu[1] = pMu[1] / 2;
	pG[1] = pG[1] / 2;
	pLambda[1] = pLambda[1] / 2;

	last = 2;

	// ��Ԫ
	for (i = 2; i <= (n - 1) - 2; ++i)
	{
		// ��i����Ԫ
		s = 2 - pLambda[i] * pMu[i - 1];
		pMu[i] = pMu[i] / s;								// ���Խ���ϵ����1
		pG[i] = (pG[i] - pLambda[i] * pG[i - 1]) / s;
		pLambda[i] = -pLambda[i] * pLambda[i - 1] / s;			// ע�⣬��ǰ��lambda��Ϊ�洢���һ��ϵ��

		// ���һ����Ԫ
		pG[(n - 1)] = pG[(n - 1)] - pMu[(n - 1)] * pG[i - 1];
		last = last - pMu[(n - 1)] * pLambda[i - 1];				// last��ʾ�������½�
		pMu[(n - 1)] = -pMu[(n - 1)] * pMu[i - 1];				// ע�⣬���һ��mu��ʾ��i�е�ϵ��
	}

	// �õ�m(n-2), m(n-1), m(n)�����Է�����
	coef[0][0] = 1;					coef[0][1] = pMu[(n - 1) - 2];	coef[0][2] = pLambda[(n - 1) - 2];	coef[0][3] = pG[(n - 1) - 2];
	coef[1][0] = pLambda[(n - 1) - 1];	coef[1][1] = 2;				coef[1][2] = pMu[(n - 1) - 1];		coef[1][3] = pG[(n - 1) - 1];;
	coef[2][0] = pMu[(n - 1)];			coef[2][1] = pLambda[(n - 1)];	coef[2][2] = last;				coef[2][3] = pG[(n - 1)];

	rtn = Gauss(3, &(coef[0][0]), &(pG[n - 3]));

	if (0 != rtn)
	{
		return rtn;
	}

	pG[0] = pG[(n - 1)];

	// �ش�
	for (i = (n - 1) - 3; i >= 1; --i)
	{
		pG[i] = pG[i] - pLambda[i] * pG[(n - 1)] - pMu[i] * pG[i + 1];
	}

lbl_spline_periodic_get_abc:

	// ������ε�a,b,c
	for (i = 0; i <= (n - 2); ++i)
	{
		hi = pX[i + 1] - pX[i];
		b = (3 * (pY[i + 1] - pY[i]) / hi - pG[i + 1] - 2 * pG[i]) / hi;
		c = (pG[i + 1] + pG[i] - 2 * (pY[i + 1] - pY[i]) / hi) / (hi*hi);

		pMu[i] = b;
		pLambda[i] = c;
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------
// 3��������ֵ��Hermite
//-------------------------------------------------------------------------------------------------
// y = yn + an(x-xn) + bn(x-xn)^2 + cn(x-xn)^3
//-------------------------------------------------------------------------------------------------
// n			����
// pX,pY		�ڵ�����
// pV			�ڵ�һ�׵���
// pC,pB,pA		��������3��������ϵ��
//-------------------------------------------------------------------------------------------------

short CSPLine::Hermite(long n, const double *pX, const double *pY, const double *pV, double *pA, double *pB, double *pC)
{
	long i;
	double deltaX, deltaY;

	if (n < 2)
	{
		return CMD_ERROR_PARAMETER;;
	}

	// pX���뵥����
	for (i = 0; i < n - 1; ++i)
	{
		if (pX[i + 1] <= pX[i])
		{
			return CMD_ERROR_PARAMETER;;
		}
	}

	for (i = 0; i < n - 1; ++i)
	{
		deltaY = pY[i + 1] - pY[i];
		deltaX = pX[i + 1] - pX[i];

		pA[i] = pV[i];
		pB[i] = (3 * deltaY / deltaX - pV[i + 1] - 2 * pV[i]) / deltaX;
		pC[i] = (pV[i + 1] + pV[i] - 2 * deltaY / deltaX) / (deltaX*deltaX);
	}

	return CMD_SUCCESS;
}

// �ٶ�ǰհ����������ڵ��ٶ�
short CSPLine::PvLookahead(long n, double *pPos, double *pVel, double *pAcc, double *pDec)
{
	long i, index;
	double s, v1, v2, acc, dec;
	double sabs, v1abs, v2abs;

	for (i = 0; i < n - 1; ++i)
	{
		index = i;

		while (1)
		{
			if (index < 0)
			{
				break;;
			}

			s = pPos[index + 1] - pPos[index];

			v1 = pVel[index];
			v2 = pVel[index + 1];

			acc = pAcc[index];
			dec = pDec[index];

			sabs = fabs(s);

			v1abs = fabs(v1);
			v2abs = fabs(v2);

			// ��������෴�������н�
			if (v1*v2 < 0)
			{
				break;
			}

			// ����ٶ���ͬ��ֻҪ�γ�����0�������н�
			if (v1 == v2)
			{
				break;
			}

			// ������ͬ
			if (v1abs < v2abs)
			{
				// �γ��㹻
				if (2 * acc*sabs >= v2*v2 - v1*v1)
				{
					break;
				}

				v2 = sqrt(2 * acc*sabs - v1*v1);

				if (s < 0)
				{
					v2 = -v2;
				}

				pVel[index + 1] = v2;

				break;
			}
			else
			{
				// �γ��㹻
				if (2 * dec*sabs >= v1*v1 - v2*v2)
				{
					break;
				}

				v1 = sqrt(2 * dec*sabs - v2*v2);

				if (s < 0)
				{
					v1 = -v1;
				}

				pVel[index] = v1;

				--index;
			}
		}
	}

	return 0;
}

//-----------------------------------------------------------------------------
// ɾ��x��ͬ�����ݵ�
//-----------------------------------------------------------------------------
// ���float(x[i]) == float(x[i+1])��ɾ��x[i+1]
//-----------------------------------------------------------------------------
short CSPLine::DeleteRedundant(long n, double *pX, double *pY, double *pV, long *pCount)
{
	long i, j, count;
	float x1, x2;

	count = n;

	i = 0;

	while (i < count - 1)
	{
		x1 = (float)pX[i];
		x2 = (float)pX[i + 1];

		if (x1 == x2)
		{
			for (j = i + 1; j < count - 1; ++j)
			{
				pX[j] = pX[j + 1];
				pY[j] = pY[j + 1];
				pV[j] = pV[j + 1];
			}

			--count;
		}
		else
		{
			++i;
		}
	}

	*pCount = count;

	return 0;
}


//-----------------------------------------------------------------------------
// ���ݰٷֱȽ���������ת��ΪS����
//-----------------------------------------------------------------------------
// ����2�����PVT
// ���2��3��4�����PVT
//-----------------------------------------------------------------------------
short CSPLine::PercentSplit(long n, double *pTime, double *pPos, double *pVel, double *pPercent, long *pCount, double *pOutTime, double *pOutPos, double *pOutVel)
{
	long i, index;
	double p;
	double v1, v2;
	double dx, dy, dv;
	double deltaXa, deltaXb;
	double deltaYa, deltaYb;
	double xa, xb, ya, yb, va, vb;

	if (n < 2)
	{
		return CMD_ERROR_PARAMETER;
	}

	index = 0;

	pOutTime[index] = pTime[0];
	pOutPos[index] = pPos[0];
	pOutVel[index] = pVel[0];

	++index;

	for (i = 0; i < n - 1; ++i)
	{
		p = pPercent[i] / 100;

		if (0 == p)
		{
			pOutTime[index] = pTime[i + 1];
			pOutPos[index] = pPos[i + 1];
			pOutVel[index] = pVel[i + 1];

			++index;

			continue;
		}

		v1 = pVel[i];
		v2 = pVel[i + 1];

		dv = v2 - v1;
		if (0 == dv)
		{
			pOutTime[index] = pTime[i + 1];
			pOutPos[index] = pPos[i + 1];
			pOutVel[index] = pVel[i + 1];

			++index;

			continue;
		}

		dx = pTime[i + 1] - pTime[i];
		dy = pPos[i + 1] - pPos[i];

		deltaXa = p*dx / 2;
		deltaXb = (1 - p)*dx;

		xa = pTime[i] + deltaXa;
		xb = xa + deltaXb;

		va = ((4 - 3 * p)*v1 + p*v2) / (4 - 2 * p);
		vb = (p*v1 + (4 - 3 * p)*v2) / (4 - 2 * p);

		deltaYa = v1*deltaXa + p*p / (2 - p) / 12 * dv*dx;
		deltaYb = (1 - p) / 2 * (v1 + v2)*dx;

		ya = pPos[i] + deltaYa;
		yb = ya + deltaYb;

		pOutTime[index] = xa;
		pOutPos[index] = ya;
		pOutVel[index] = va;

		++index;

		if (deltaXb > 0)
		{
			pOutTime[index] = xb;
			pOutPos[index] = yb;
			pOutVel[index] = vb;

			++index;
		}

		pOutTime[index] = pTime[i + 1];
		pOutPos[index] = pPos[i + 1];
		pOutVel[index] = pVel[i + 1];

		++index;
	}

	// ɾ����������
	DeleteRedundant(index, pOutTime, pOutPos, pOutVel, pCount);

	return 0;
}

//-----------------------------------------------------------------------------
// v1��v2������ͬ
//-----------------------------------------------------------------------------
// s����2��֮���λ�ƣ������ɸ�
// v1����ٶȣ�v2�յ��ٶȣ������ɸ�
// v����2��֮�������ٶȣ�����
// acc����2��֮��ļ��ٶ�
// dec����2��֮��ļ��ٶ�
// pTime��ֳ��ĸ���ʱ������
// pPos��ֳ��ĸ���λ������
// pVel��ֳ��ĸ����յ��ٶ�
// ���ز�ֳ��Ķ���
//-----------------------------------------------------------------------------
short CSPLine::PvSplitSame(double s, double v1, double v2, double v, double acc, double dec, long *pCount, double *pTime, double *pPos, double *pVel)
{
	double sa, sd;
	double sabs, v1abs, v2abs;

	sabs = fabs(s);
	v1abs = fabs(v1);
	v2abs = fabs(v2);

	sa = (v*v - v1*v1) / 2 / acc;
	sd = (v*v - v2*v2) / 2 / dec;

	// �ܹ��ﵽ����ٶ�
	if (sabs > sa + sd)
	{
		// ֻ�����ٶ�
		if ((v1abs == v) && (v2abs == v))
		{
			pTime[0] = sabs / v;
			pPos[0] = s;
			pVel[0] = v1;

			*pCount = 1;
			return 0;
		}

		// ���ٶΡ����ٶ�
		if ((v1abs < v) && (v2abs == v))
		{
			pTime[0] = (v - v1abs) / acc;
			pTime[1] = (sabs - sa) / v;

			pVel[0] = v2;
			pVel[1] = v2;

			if (s > 0)
			{
				pPos[0] = sa;
				pPos[1] = sabs - sa;
			}
			else
			{
				pPos[0] = -sa;
				pPos[1] = -(sabs - sa);
			}

			*pCount = 2;
			return 0;
		}

		// ���ٶΡ����ٶ�
		if ((v1abs == v) && (v2abs < v))
		{
			pTime[0] = (sabs - sd) / v;
			pTime[1] = (v - v2abs) / dec;

			pVel[0] = v1;
			pVel[1] = v2;

			if (s > 0)
			{
				pPos[0] = sabs - sd;
				pPos[1] = sd;
			}
			else
			{
				pPos[0] = -(sabs - sd);
				pPos[1] = -sd;
			}

			*pCount = 2;
			return 0;
		}

		// ���ٶΡ����ٶΡ����ٶ�
		pTime[0] = (v - v1abs) / acc;
		pTime[1] = (sabs - sa - sd) / v;
		pTime[2] = (v - v2abs) / dec;

		if (s > 0)
		{
			pPos[0] = sa;
			pPos[1] = sabs - sa - sd;
			pPos[2] = sd;

			pVel[0] = v;
			pVel[1] = v;
			pVel[2] = v2;
		}
		else
		{
			pPos[0] = -sa;
			pPos[1] = -(sabs - sa - sd);
			pPos[2] = -sd;

			pVel[0] = -v;
			pVel[1] = -v;
			pVel[2] = v2;
		}

		*pCount = 3;
		return 0;
	}

	// ����ʵ���ܹ��ﵽ������ٶ�
	v = sqrt((dec*v1*v1 + acc*v2*v2 + 2 * acc*dec*sabs) / (acc + dec));

	pTime[0] = (v - v1abs) / acc;
	pTime[1] = (v - v2abs) / dec;

	sa = (v*v - v1*v1) / 2 / acc;

	if (s > 0)
	{
		pPos[0] = sa;
		pPos[1] = sabs - sa;

		pVel[0] = v;
	}
	else
	{
		pPos[0] = -sa;
		pPos[1] = -(sabs - sa);

		pVel[0] = -v;
	}

	pVel[1] = v2;

	*pCount = 2;
	return 0;
}


//-----------------------------------------------------------------------------
// v1��v2�����෴
//-----------------------------------------------------------------------------
// s����2��֮���λ�ƣ������ɸ�
// v1����ٶȣ�v2�յ��ٶȣ������ɸ�
// v����2��֮�������ٶȣ�����
// acc����2��֮��ļ��ٶ�
// dec����2��֮��ļ��ٶ�
// pTime��ֳ��ĸ���ʱ������
// pPos��ֳ��ĸ���λ������
// pVel��ֳ��ĸ����յ��ٶ�
// ���ز�ֳ��Ķ���
//-----------------------------------------------------------------------------
short CSPLine::PvSplitDifferent(double s, double v1, double v2, double v, double acc, double dec, long *pCount, double *pTime, double *pPos, double *pVel)
{
	double sabs, v1abs, v2abs;
	double s1, s2;
	long count;

	sabs = fabs(s);
	v1abs = fabs(v1);
	v2abs = fabs(v2);

	if (v1 > 0)
	{
		s1 = v1*v1 / 2 / dec;
		s2 = -v2*v2 / 2 / acc;

		if (s > s1 + s2)
		{
			s1 = s - s2;
			PvSplitSame(s1, v1, 0, v, acc, dec, &count, pTime, pPos, pVel);

			pTime[count] = fabs(v2) / acc;
			pPos[count] = s2;
			pVel[count] = v2;

			*pCount = count + 1;

			return 0;
		}
		else if (s < s1 + s2)
		{
			pTime[0] = v1 / dec;
			pPos[0] = s1;
			pVel[0] = 0;

			s2 = s - s1;
			PvSplitSame(s2, 0, v2, v, acc, dec, &count, &pTime[1], &pPos[1], &pVel[1]);

			*pCount = count + 1;
			return 0;
		}
	}
	else
	{
		s1 = -v1*v1 / 2 / dec;
		s2 = v2*v2 / 2 / acc;

		if (s > s1 + s2)
		{
			pTime[0] = fabs(v1) / dec;
			pPos[0] = s1;
			pVel[0] = 0;

			s2 = s - s1;
			PvSplitSame(s2, 0, v2, v, acc, dec, &count, &pTime[1], &pPos[1], &pVel[1]);

			*pCount = count + 1;
			return 0;
		}
		else if (s < s1 + s2)
		{
			s1 = s - s2;
			PvSplitSame(s1, v1, 0, v, acc, dec, &count, pTime, pPos, pVel);

			pTime[count] = v2 / acc;
			pPos[count] = s2;
			pVel[count] = v2;

			*pCount = count + 1;
			return 0;
		}
	}

	pTime[0] = fabs(v1) / dec;
	pTime[1] = fabs(v2) / acc;

	pPos[0] = s1;
	pPos[1] = s2;

	pVel[0] = 0;
	pVel[1] = v2;

	*pCount = 2;
	return 0;
}

//-----------------------------------------------------------------------------
// ��������2��֮��ļӼ�������
//-----------------------------------------------------------------------------
// ����n�����PVT
// ���count�����PVT������2��֮���ٶȶ�������
//-----------------------------------------------------------------------------
short CSPLine::PvSplit(long n, double time, double *pPos, double *pVel, double *pVelMax, double *pAcc, double *pDec, long *pCount, double *pOutTime, double *pOutPos, double *pOutVel)
{
	long i, j, index, count;
	double s, v1, v2, v, acc, dec;
	double dt[4], ds[4], vel[4];

	pOutTime[0] = time;
	pOutPos[0] = pPos[0];
	pOutVel[0] = pVel[0];

	index = 1;

	for (i = 0; i < n - 1; ++i)
	{
		s = pPos[i + 1] - pPos[i];

		v1 = pVel[i];
		v2 = pVel[i + 1];

		v = pVelMax[i];

		acc = pAcc[i];
		dec = pDec[i];

		// �����෴
		if (v1*v2 < 0)
		{
			PvSplitDifferent(s, v1, v2, v, acc, dec, &count, dt, ds, vel);
		}
		// ������ͬ
		else
		{
			PvSplitSame(s, v1, v2, v, acc, dec, &count, dt, ds, vel);
		}

		for (j = 0; j < count; ++j)
		{
			pOutTime[index] = pOutTime[index - 1] + dt[j];
			pOutPos[index] = pOutPos[index - 1] + ds[j];
			pOutVel[index] = vel[j];

			++index;
		}
	}

	DeleteRedundant(index, pOutTime, pOutPos, pOutVel, pCount);

	return 0;
}
