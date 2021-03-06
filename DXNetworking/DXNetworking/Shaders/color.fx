//=============================================================================
// color.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Basic FX that simply transforms geometry from local space to 
// homogeneous clip space, and draws the geometry in solid color.
//=============================================================================

uniform extern float4x4 gWVP;
uniform extern float4 CustCol;


struct OutputVS
{
    float4 posH  : POSITION0;
    float4 color : COLOR0;
};


OutputVS ColorVS(float3 posL : POSITION0, float4 c : COLOR0)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	
	// Just pass the vertex color into the pixel shader.
	outVS.color = c;
	 
	// Done--return the output.
    return outVS;
}

float4 ColorPS(float4 c : COLOR0) : COLOR
{
	return CustCol;
    //return c;
	//return float4(0.0f, 1.0f, 0.0f, 1.0f);
}

technique ColorTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_3_0 ColorVS();
        pixelShader  = compile ps_3_0 ColorPS();
    }
}