//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// GunShip
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string GunShip_Pass_0_Model: ModelData = "C:\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4 g_stColor;
float4 g_stColor_Light;

float4x4 g_stMatrix_World: World;
float4x4 g_stMatrix_View: View;
float4x4 g_stMatrix_Projection: Projection;

/** VS Input */
struct STVSInput
{
	float3 m_stPos: POSITION;
	float3 m_stNormal: NORMAL;
	float3 m_stTangent: TANGENT;
	float3 m_stBinormal: BINORMAL;
	float2 m_stUV: TEXCOORD0;
};

/** VS Output */
struct STVSOutput
{
	float4 m_stPos: SV_POSITION;
	float3 m_stNormal: TEXCOORD0;
	float3 m_stTangent: TEXCOORD1;
	float3 m_stBinormal: TEXCOORD2;
	float2 m_stUV: TEXCOORD3;
};

/** VS Main */
STVSOutput GunShip_Pass_0_Vertex_Shader_VSMain(STVSInput a_stInput)
{
	STVSOutput stOutput = (STVSOutput)0;
	float4 stPos_World = mul(float4(a_stInput.m_stPos, 1.0f), g_stMatrix_World);
	
	stOutput.m_stPos = mul(stPos_World, g_stMatrix_View);
	stOutput.m_stPos = mul(stOutput.m_stPos, g_stMatrix_Projection);
	
	float3 stNormal = mul(a_stInput.m_stNormal, (float3x3)g_stMatrix_World);
	stOutput.m_stNormal = normalize(stNormal);
	
	float3 stTangent = mul(a_stInput.m_stTangent, (float3x3)g_stMatrix_World);
	stOutput.m_stTangent = normalize(stTangent);
	
	float3 stBinormal = mul(a_stInput.m_stBinormal, (float3x3)g_stMatrix_World);
	stOutput.m_stBinormal = normalize(stBinormal);
	
	stOutput.m_stUV = a_stInput.m_stUV;
	return stOutput;
}

/** PS Input */
struct STPSInput
{
	float4 m_stPos: SV_POSITION;
	float3 m_stNormal: TEXCOORD0;
	float3 m_stTangent: TEXCOORD1;
	float3 m_stBinormal: TEXCOORD2;
	float2 m_stUV: TEXCOORD3;
};

/** PS Main */
float4 GunShip_Pass_0_Pixel_Shader_PSMain(STPSInput a_stInput): SV_TARGET
{
	return float4(0.0f, 1.0f, 0.0f, 1.0f);
}

//--------------------------------------------------------------//
// Technique Section for GunShip
//--------------------------------------------------------------//
technique10 GunShip
{
	pass Pass_0
	{
		SetVertexShader(CompileShader(vs_4_0, GunShip_Pass_0_Vertex_Shader_VSMain()));
		SetPixelShader(CompileShader(ps_4_0, GunShip_Pass_0_Pixel_Shader_PSMain()));

	}

}

