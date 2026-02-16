#pragma once

#include <d3d11.h>

#define DDS_MAGIC 0x20534444

#define DDPF_FOURCC 0x4
#define DDPF_RGB    0x40

#define MAKEFOURCC_DXT1 0x31545844
#define MAKEFOURCC_DXT3 0x33545844
#define MAKEFOURCC_DXT5 0x35545844

typedef struct {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwFourCC;
    DWORD dwRGBBitCount;
    DWORD dwRBitMask;
    DWORD dwGBitMask;
    DWORD dwBBitMask;
    DWORD dwABitMask;
} DDS_PIXELFORMAT_t;

typedef struct {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwHeight;
    DWORD dwWidth;
    DWORD dwPitchOrLinearSize;
    DWORD dwDepth;
    DWORD dwMipMapCount;
    DWORD dwReserved1[11];
    DDS_PIXELFORMAT_t ddspf;
    DWORD dwCaps;
    DWORD dwCaps2;
    DWORD dwCaps3;
    DWORD dwCaps4;
    DWORD dwReserved2;
} DDS_HEADER_t;

static inline HRESULT LoadDDSTexture(ID3D11Device* device, const wchar_t* filename, ID3D11ShaderResourceView** srv)
{
    HANDLE hFile = CreateFileW(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return E_FAIL;

    DWORD fileSize = GetFileSize(hFile, NULL);
    BYTE* fileData = (BYTE*)HeapAlloc(GetProcessHeap(), 0, fileSize);
    if (!fileData) {
        CloseHandle(hFile);
        return E_OUTOFMEMORY;
    }

    DWORD bytesRead;
    if (!ReadFile(hFile, fileData, fileSize, &bytesRead, NULL) || bytesRead != fileSize) {
        HeapFree(GetProcessHeap(), 0, fileData);
        CloseHandle(hFile);
        return E_FAIL;
    }
    CloseHandle(hFile);

    if (fileSize < sizeof(DWORD) + sizeof(DDS_HEADER_t)) {
        HeapFree(GetProcessHeap(), 0, fileData);
        return E_FAIL;
    }

    DWORD magic = *(DWORD*)fileData;
    if (magic != DDS_MAGIC) {
        HeapFree(GetProcessHeap(), 0, fileData);
        return E_FAIL;
    }

    DDS_HEADER_t* header = (DDS_HEADER_t*)(fileData + sizeof(DWORD));
    DWORD width = header->dwWidth;
    DWORD height = header->dwHeight;
    BYTE* pixelData = fileData + sizeof(DWORD) + sizeof(DDS_HEADER_t);

    DXGI_FORMAT format;
    UINT rowPitch;
    UINT dataSize;
    BOOL compressed = FALSE;

    if (header->ddspf.dwFlags & DDPF_FOURCC) {
        compressed = TRUE;
        UINT blockSize;
        switch (header->ddspf.dwFourCC) {
            case MAKEFOURCC_DXT1:
                format = DXGI_FORMAT_BC1_UNORM;
                blockSize = 8;
                break;
            case MAKEFOURCC_DXT3:
                format = DXGI_FORMAT_BC2_UNORM;
                blockSize = 16;
                break;
            case MAKEFOURCC_DXT5:
                format = DXGI_FORMAT_BC3_UNORM;
                blockSize = 16;
                break;
            default:
                HeapFree(GetProcessHeap(), 0, fileData);
                return E_FAIL;
        }
        UINT blocksWide = (width + 3) / 4;
        UINT blocksHigh = (height + 3) / 4;
        width = blocksWide * 4;
        height = blocksHigh * 4;
        rowPitch = blocksWide * blockSize;
        dataSize = rowPitch * blocksHigh;
    } else if (header->ddspf.dwFlags & DDPF_RGB) {
        if (header->ddspf.dwRGBBitCount == 32) {
            format = DXGI_FORMAT_B8G8R8A8_UNORM;
            rowPitch = width * 4;
            dataSize = rowPitch * height;
        } else {
            HeapFree(GetProcessHeap(), 0, fileData);
            return E_FAIL;
        }
    } else {
        HeapFree(GetProcessHeap(), 0, fileData);
        return E_FAIL;
    }

    D3D11_TEXTURE2D_DESC texDesc;
    ZeroMemory(&texDesc, sizeof(texDesc));
    texDesc.Width = width;
    texDesc.Height = height;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = format;
    texDesc.SampleDesc.Count = 1;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory(&initData, sizeof(initData));
    initData.pSysMem = pixelData;
    initData.SysMemPitch = rowPitch;

    ID3D11Texture2D* tex = NULL;
    HRESULT hr = device->lpVtbl->CreateTexture2D(device, &texDesc, &initData, &tex);
    if (FAILED(hr)) {
        HeapFree(GetProcessHeap(), 0, fileData);
        return hr;
    }

    hr = device->lpVtbl->CreateShaderResourceView(device, (ID3D11Resource*)tex, NULL, srv);
    tex->lpVtbl->Release(tex);
    HeapFree(GetProcessHeap(), 0, fileData);
    return hr;
}
