﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DownsampleShader : MonoBehaviour
{

    [SerializeField] private RenderTexture renderTexture;
    [SerializeField] private float downScale;

    private void OnRenderImage(RenderTexture source, RenderTexture destination)
    {
        // Apply the material/shader to the camera RenderTexture.
        Graphics.Blit(renderTexture, destination);
    }

}
