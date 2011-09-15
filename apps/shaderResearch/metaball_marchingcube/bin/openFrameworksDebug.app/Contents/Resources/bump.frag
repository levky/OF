// Image texture.
uniform sampler2D ImageTexture;

// Width of Image.
uniform float fWidth;
// Height of Image.
uniform float fHeight;
// Indicating cartoon effect is enabled or not.
uniform float fCartoonEffect;

void main()
{
    // X directional search matrix.
    mat3 GX = mat3( -1.0, 0.0, 1.0,
                    -2.0, 0.0, 2.0,
                    -1.0, 0.0, 1.0 );
    // Y directional search matrix.
    mat3 GY =  mat3( 1.0,  2.0,  1.0,
                     0.0,  0.0,  0.0,
                    -1.0, -2.0, -1.0 );

    vec4  fSumX = vec4( 0.0,0.0,0.0,0.0 );
    vec4  fSumY = vec4( 0.0,0.0,0.0,0.0 );
    vec4 fTotalSum = vec4( 0.0,0.0,0.0,0.0 );

    // Findout X , Y index of incoming pixel
    // from its texture coordinate.
    float fXIndex = gl_TexCoord[0].s * fWidth;
    float fYIndex = gl_TexCoord[0].t * fHeight;

    /* image boundaries Top, Bottom, Left, Right pixels*/
    if( ! ( fYIndex < 1.0 || fYIndex > fHeight - 1.0 || 
            fXIndex < 1.0 || fXIndex > fWidth - 1.0 ))
    {
        // X Directional Gradient calculation.
        for(float I=-1.0; I<=1.0; I = I + 1.0)
        {
            for(float J=-1.0; J<=1.0; J = J + 1.0)
            {
                float fTempX = ( fXIndex + I + 0.5 ) / fWidth ;
                float fTempY = ( fYIndex + J + 0.5 ) / fHeight ;
                vec4 fTempSumX = texture2D( ImageTexture, vec2( fTempX, fTempY ));
                fSumX = fSumX + ( fTempSumX * vec4( GX[int(I+1.0)][int(J+1.0)],
                                                    GX[int(I+1.0)][int(J+1.0)],
                                                    GX[int(I+1.0)][int(J+1.0)],
                                                    GX[int(I+1.0)][int(J+1.0)]));
            }
        }

        { // Y Directional Gradient calculation.
            for(float I=-1.0; I<=1.0; I = I + 1.0)
            {
                for(float J=-1.0; J<=1.0; J = J + 1.0)
                {
                    float fTempX = ( fXIndex + I + 0.5 ) / fWidth ;
                    float fTempY = ( fYIndex + J + 0.5 ) / fHeight ;
                    vec4 fTempSumY = texture2D( ImageTexture, vec2( fTempX, fTempY ));
                    fSumY = fSumY + ( fTempSumY * vec4( GY[int(I+1.0)][int(J+1.0)],
                                                        GY[int(I+1.0)][int(J+1.0)],
                                                        GY[int(I+1.0)][int(J+1.0)],
                                                        GY[int(I+1.0)][int(J+1.0)]));
                }
            }
            // Combine X Directional and Y Directional Gradient.
            vec4 fTem = fSumX * fSumX + fSumY * fSumY;
            fTotalSum = sqrt( fTem );
        }
    }
    // Checking status of cartoon effect.
    if( 0.5 < fCartoonEffect )
    {
        // Creaing cartoon effect by combining
        // edge informatioon and original image data.
        fTotalSum = mix( fTotalSum, texture2D( ImageTexture, 
                         vec2( gl_TexCoord[0].s, gl_TexCoord[0].t)), 0.5);
    }
    else
    {
        // Creating displayable edge data.
        fTotalSum = vec4( 1.0,1.0,1.0,1.0) - fTotalSum;
    }
    
    gl_FragColor = ( fTotalSum );
}