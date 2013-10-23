cbuffer Constants : register ( b0 )
{
	matrix	viewProj;
};


struct VertexInput
{
	float4 pos		: POSITION;
	float4 color	: COLOR;
};


void LineVS( in VertexInput input, out float4 color : COLOR0, out float4 screenpos : SV_Position )
{
	color = input.color;
	screenpos = mul( float4( input.pos.xyz, 1 ), viewProj );
}


float4 LinePS( in float4 color : COLOR0 ) : SV_Target
{
	return color;
};