    #version 330 core
    out vec4 FragColor;
	in vec2 TexCoord;

	struct Material {
	    vec3 ambient;
	    sampler2D texture_diffuse;
	    sampler2D texture_specular;
	    float shininess;
	};
	struct LightDirection {
		 vec3 pos;
		 vec3 color;
		 vec3 dirToLight;
	};


	struct LightPoint {
		vec3 pos;
		vec3 color;
		vec3 dirToLight;

	    float constant;
	    float linear;
	    float quadratic;
	};

	struct LightSpot {
		vec3 pos;
		vec3 color;
		vec3 dirToLight;

		float constant;
	    float linear;
	    float quadratic;

	    float cosPhyIn;
		float cosPhyOut;

	};

	uniform Material material;
	uniform LightDirection lightDirection;

	uniform LightPoint lightPoint;
	uniform LightPoint lightPoint1;
	uniform LightPoint lightPoint2;
	uniform LightPoint lightPoint3;

	uniform LightSpot lightSpot;

	in vec3 FragPos;
	in vec3 Normal;

//	uniform sampler2D texture1;
//	uniform sampler2D texture2;
	uniform vec3 objColor;
	uniform vec3 ambientcolor;
	uniform vec3 LightPos;
	uniform vec3 LightColor;
//	uniform vec3 LightDirUniform;
	uniform vec3 CameraPos;


	vec3 DirectionLight(LightDirection light , vec3 normal , vec3 dirToCamera)
	{
		// diffsue
		float diffuseAmount = max(dot(light.dirToLight,normal),0);
		vec3 diffuseColor = diffuseAmount * light.color *texture(material.texture_diffuse , TexCoord ).rgb;


		//specular
		vec3 ReflectDir = normalize(reflect(-light.dirToLight , normal));
		float specularAmount =  pow(max(dot(ReflectDir , dirToCamera),0),material.shininess);
		vec3 specularColor = specularAmount * light.color * texture(material.texture_specular , TexCoord ).rgb;

		vec3 result = diffuseColor + specularColor;

		return result;
	}

	vec3 PointLight(LightPoint light , vec3 normal , vec3 dirToCamera)
	{

		//attenution
		float dist  = length(light.pos - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * dist +  light.quadratic * (dist * dist));


		// diffsue
		float diffuseAmount = max(dot(normalize(light.pos - FragPos),normal),0) ;
		vec3 diffuseColor = diffuseAmount * light.color *texture(material.texture_diffuse , TexCoord ).rgb;


		//specular
		vec3 ReflectDir = normalize(reflect(-normalize(light.pos - FragPos) , normal));
		float specularAmount =  pow(max(dot(ReflectDir , dirToCamera),0),material.shininess) ;
		vec3 specularColor = specularAmount * light.color * texture(material.texture_specular , TexCoord ).rgb;

		vec3 result = (diffuseColor + specularColor) * attenuation;

		return result;
	}

	vec3 SpotLight(LightSpot light , vec3 normal , vec3 dirToCamera)
	{
		//attenution
		float dist  = length(light.pos - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * dist +  light.quadratic * (dist * dist));

		float cosTheta = -dot( normalize(FragPos - light.pos),-1 * light.dirToLight );
		float spotRatio = clamp((cosTheta - lightSpot.cosPhyOut) / (lightSpot.cosPhyIn - lightSpot.cosPhyOut),0,1);

		// diffsue
		float diffuseAmount = max(dot(normalize(light.pos - FragPos),normal),0) ;
		vec3 diffuseColor = diffuseAmount * light.color *texture(material.texture_diffuse , TexCoord ).rgb;


		//specular
		vec3 ReflectDir = normalize(reflect(-normalize(light.pos - FragPos) , normal));
		float specularAmount =  pow(max(dot(ReflectDir , dirToCamera),0),material.shininess) ;
		vec3 specularColor = specularAmount * light.color * texture(material.texture_specular , TexCoord ).rgb;

		vec3 result = (diffuseColor + specularColor) * attenuation * spotRatio;

		return result;
	}

    void main()
    {
		vec3 FinalResult = vec3(0,0,0);
		vec3 Unormal = normalize(Normal);
		vec3 DirToCamera = normalize(CameraPos - FragPos);
		FinalResult += DirectionLight(lightDirection , Unormal , DirToCamera);

		FinalResult += PointLight(lightPoint , Unormal , DirToCamera);
		FinalResult += PointLight(lightPoint1 , Unormal , DirToCamera);
		FinalResult += PointLight(lightPoint2 , Unormal , DirToCamera);
		FinalResult += PointLight(lightPoint3 , Unormal , DirToCamera);

		FinalResult += SpotLight(lightSpot , Unormal , DirToCamera);

		FragColor = vec4(FinalResult ,1.0f);

    };