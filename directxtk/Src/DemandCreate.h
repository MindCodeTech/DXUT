//--------------------------------------------------------------------------------------
// File: DemandCreate.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#pragma once

#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
	extern "C++" {
#endif

namespace DirectX
{
    // Helper for lazily creating a D3D resource.
    template<typename T, typename TCreateFunc>
    static T* DemandCreate(Microsoft::WRL::ComPtr<T>& comPtr, std::mutex& mutex, TCreateFunc createFunc)
    {
        T* result = comPtr.Get();

        // Double-checked lock pattern.
        MemoryBarrier();

        if (!result)
        {
            std::lock_guard<std::mutex> lock(mutex);

            result = comPtr.Get();
        
            if (!result)
            {
                // Create the new object.
                ThrowIfFailed(
                    createFunc(&result)
                );

                MemoryBarrier();

                comPtr.Attach(result);
            }
        }

        return result;
    }
}

#if defined(extern_cplus) && defined(extern_cplusplus)
	}
	}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
}
#endif
