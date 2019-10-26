#include "stdafx.h"
#pragma hdrstop

CBackend RCache;

// Igor: is used to test bug with rain, particles corruption
void CBackend::RestoreQuadIBData()
{
    // Igor: never seen this corruption for DX10
    ;
}

void CBackend::CreateQuadIB()
{
    constexpr auto triCount = 4 * 1024;
    constexpr auto idxCount = triCount * 2 * 3;
    constexpr auto idxSize = idxCount * sizeof(u16);

    QuadIB.Create(idxSize);

    u16* Indices = static_cast<u16*>(QuadIB.Map());
    {
        int Cnt = 0;
        int ICnt = 0;
        for (int i = 0; i < triCount; i++)
        {
            Indices[ICnt++] = u16(Cnt + 0);
            Indices[ICnt++] = u16(Cnt + 1);
            Indices[ICnt++] = u16(Cnt + 2);

            Indices[ICnt++] = u16(Cnt + 3);
            Indices[ICnt++] = u16(Cnt + 2);
            Indices[ICnt++] = u16(Cnt + 1);

            Cnt += 4;
        }
    }
    QuadIB.Flush();
}

// Device dependance
void CBackend::OnDeviceCreate()
{
    CreateQuadIB();

    // streams
    Vertex.Create();
    Index.Create();

    // invalidate caching
    Invalidate();
}

void CBackend::OnDeviceDestroy()
{
    // streams
    Index.Destroy();
    Vertex.Destroy();

    // Quad
    QuadIB.Release();
}
