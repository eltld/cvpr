#include "stdafx.h"
#include "Dib.h"
#include "DibSegment.h"
#include "DibEnhancement.h"
ContourPoints DibContourTracing(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	int x, y, nx, ny;
	int dold, d, cnt;
	//���� ������ ��Ÿ���� �迭
	int dir[8][2] = {
		{1,0},
		{1,1},
		{0,1},
		{-1,1},
		{-1,0},
		{-1,-1},
		{0,-1},
		{1, -1}
	};

	//�ܰ��� ��ǥ�� ������ ����ü
	ContourPoints cp;
	cp.num = 0;

	for (j = 0; j < w; j++)
		for (i = 0; i < h; i++)
		{
			//��ü�� ���
			if (ptr[j][i] != 0)
			{
				x = i;
				y = j;

				dold = d = cnt = 0;

				while (1)
				{
					nx = x + dir[d][0];
					ny = y + dir[d][1];

					if (nx < 0 || nx >= w || ny < 0 || ny >= h || ptr[ny][nx] == 0)
					{
						//���� ���⿡ �ִ� �ȼ��� ��ü�� �ƴѰ��,
						//�ð� �������� ���� ������ �ٲٰ� �ٽ� �õ�
						if (++d > 7)
							d = 0;
						cnt++;

						//8���� ��� ���(background)�� ���
						if (cnt >= 8)
						{
							cp.x[cp.num] = x;
							cp.y[cp.num] = y;
							cp.num++;

							//�ܰ��� ������ ����.
							break;
						}
					}
					else
					{
						//���� ������ �ȼ��� ��ü�� ���
						//���� ���� �ܰ��� ������ ����
						cp.x[cp.num] = x;
						cp.y[cp.num] = y;
						cp.num++;

						//�ܰ��� �ȼ��� �ʹ� ������ ���� ����
						if (cp.num >= MAX_CONTOUR)
							break;

						//���� �������� �̵�

						x = nx;
						y = ny;

						//���� ���� �ʱ�ȭ
						cnt = 0;
						dold = d;
						//d = dold -2 �� ���� ����
						d = (dold + 6) % 8;
					}
					//���������� ���ƿ��� ��������� �ʱ�ȭ�� ���
					//�ܰ��� ���� ����
					if (x == i && y == j &&d == 0)
						break;
				}
				//for������ ������ �����ϱ� ���� i,j���� ����
				i = w; j = h;
			}
		}
	return cp;
}
int DibLabeling(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();
	//�ӽ÷� ���̺��� ������ �޸� ������ � ���̺� ����
	int** map = new int*[h];

	for (i = 0; i < h; i++)
	{
		map[i] = new int[w];
		memset(map[i], 0, sizeof(int)*w);
	}
	int eq_tbl[MAX_LABEL][2] = { { 0, }, };

	int label = 0, maxl, minl, min_eq, max_eq;

	for (j = 1; j < h; j++)
		for (i = 1; i < w; i++)
		{
			if (ptr[j][i] != 0)
			{
				//�ٷ� �� �ȼ��� ���� �ȼ� ��ο� ���̺��� �����ϴ� ���
				if ((map[j - 1][i] != 0) && (map[j][i - 1] != 0))
				{
					if (map[j - 1][i] == map[j][i - 1])
					{
						//�� ���̺��� ���� ���� ���
						map[j][i] = map[j - 1][i];
					}
					else
					{
						//�� ���̺��� ���� �ٸ����, ���� ���̺��� �ο�
						maxl = max(map[j - 1][i], map[j][i - 1]);
						minl = min(map[j - 1][i], map[j][i - 1]);

						map[j][i] = minl;
						//� ���̺� ����
						min_eq = min(eq_tbl[maxl][1], eq_tbl[minl][1]);
						max_eq = max(eq_tbl[maxl][1], eq_tbl[minl][1]);

						eq_tbl[maxl][1] = min_eq;
						eq_tbl[minl][1] = min_eq;
					}
				}
				else if (map[j - 1][i] != 0)
				{
					//�ٷ� �� �ȼ����� ���̺��� ������ ���
					map[j][i] = map[j - 1][i];
				}
				else if (map[j][i - 1] != 0)
				{
					//�ٷ� ���� �ȼ����� ���̺��� ������ ���
					map[j][i] = map[j][i - 1];
				}
				else
				{
					//�̿��� ���̺��� �������� ������ ���ο� ���̺��� �ο�
					label++;
					map[j][i] = label;
					eq_tbl[label][0] = label;
					eq_tbl[label][1] = label;
				}
			}
		}
	//� ���̺� ����
	int temp;
	for (i = 1; i <= label; i++)
	{
		temp = eq_tbl[i][1];
		if (temp != eq_tbl[i][0])
			eq_tbl[i][1] = eq_tbl[temp][1];
	}
	
	// � ���̺��� ���̺��� 1���� ���ʴ�� ������Ű��

	int* hash = new int[label + 1];
	memset(hash, 0, sizeof(int)*(label + 1));

	for (i = 1; i <= label; i++)
		hash[eq_tbl[i][1]] = eq_tbl[i][1];

	int label_cnt = 1;
	for (i = 1; i <= label; i++)
		if (hash[i] != 0)
			hash[i] = label_cnt++;

	for (i = 1; i <= label; i++)
		eq_tbl[i][1] = hash[eq_tbl[i][1]];

	delete[] hash;
	//�ι�° ��ĵ, ����̺��� �̿��Ͽ� ��� �ȼ��� ������ ���̺� �ο�

	dib.CreateGrayImage(w, h, 0);
	ptr = dib.GetPtr();

	for (j = 1; j < h; j++)
		for (i = 1; i < w; i++)
		{
			if (map[j][i] != 0)
			{
				temp = map[j][i];
				ptr[j][i] = (BYTE)(eq_tbl[temp][1]);
			}
		}

	//�ӽ� �޸� ���� ����

	for (i = 0; i < h; i++)
		delete[] map[i];
	delete[] map;
	return (label_cnt - 1);
}
void DibBinarization(CDib& dib, int th)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
			ptr[j][i] = (ptr[j][i] > th) ? 255 : 0;
}
int DibBinarizationIterative(CDib& dib)
{
	register int i;


	int w = dib.GetWidth();
	int h = dib.GetHeight();

	float hist[256] = { 0, };

	DibHistogram(dib, hist);

	int T, Told;

	float sum = 0.f;

	for (i = 0; i < 256; i++)
		sum += (i*hist[i]);
	T = (int)sum;

	float a1, b1, u1, a2, b2, u2;
	do
	{
		Told = T;

		a1 = b1 = 0;

		for (i = 0; i <= Told; i++)
		{
			a1 += (i*hist[i]);
			b1 += hist[i];
		}
		u1 = a1 / b1;

		a2 = b2 = 0;
		for (i = Told + 1; i < 256; i++)
		{
			a2 += (i*hist[i]);
			b2 += hist[i];
		}
		u2 = a2 / b2;
		if (b1 == 0)
			b1 = 1.f;
		if (b2 == 0)
			b2 = 1.f;

		T = (int)((u1 + u2) / 2);
	} while (T == Told);
	return T;
}