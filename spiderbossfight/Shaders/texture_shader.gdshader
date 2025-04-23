shader_type spatial;

// Base textures
uniform sampler2D terrain_grass : source_color;
uniform sampler2D terrain_rock : source_color;
uniform sampler2D terrain_grass_normal : hint_normal;
uniform sampler2D terrain_rock_normal : hint_normal;
uniform sampler2D noise_texture : hint_default_white;

// Height control parameters
uniform float grass_min_height = -1.0;
uniform float grass_max_height = 2.0;
uniform float transition_softness = 1.0;

// Texture control parameters
uniform vec2 uv_scale = vec2(10.0);
uniform float normal_strength = 1.0;
uniform float terrain_smoothing = 0.5;

// Grass effect parameters
uniform float grass_blade_height = 0.4;
uniform float grass_blade_width = 0.05;
uniform float grass_density = 0.8;
uniform vec3 grass_color = vec3(0.3, 0.5, 0.15);
uniform vec3 grass_color_variation = vec3(0.1, 0.1, 0.05);
uniform float wind_strength = 0.2;
uniform float wind_speed = 1.0;
uniform float grass_randomness = 0.5;

// Global parameters
uniform vec3 wind_direction = vec3(1.0, 0.0, 0.3);

// Variables passed between functions
varying float vertex_y;
varying vec3 vertex_normal;
varying vec3 vertex_position;
varying vec2 world_position;

// Utility functions
float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

vec2 hash2(vec2 p) {
    p = vec2(dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3)));
    return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);
}

// Improved Perlin noise function
float perlin_noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);

    // Cubic Hermite interpolation
    vec2 u = f * f * (3.0 - 2.0 * f);

    // Gradients
    float a = dot(hash2(i), f);
    float b = dot(hash2(i + vec2(1.0, 0.0)), f - vec2(1.0, 0.0));
    float c = dot(hash2(i + vec2(0.0, 1.0)), f - vec2(0.0, 1.0));
    float d = dot(hash2(i + vec2(1.0, 1.0)), f - vec2(1.0, 1.0));

    // Mix
    return mix(mix(a, b, u.x), mix(c, d, u.x), u.y) * 0.5 + 0.5;
}

// Improved fractal Brownian motion
float fbm(vec2 p, int octaves) {
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 1.0;

    for (int i = 0; i < octaves; i++) {
        value += amplitude * perlin_noise(p * frequency);
        amplitude *= 0.5;
        frequency *= 2.0;
    }

    return value;
}

void vertex() {
    // Store the original vertex position
    vertex_y = VERTEX.y;
    vertex_normal = NORMAL;
    vertex_position = VERTEX;

    // Get world position for consistent noise sampling
    world_position = (MODEL_MATRIX * vec4(VERTEX, 1.0)).xz;

    // Apply terrain smoothing using noise
    if (terrain_smoothing > 0.0) {
        float noise_value = texture(noise_texture, world_position * 0.01).r;
        VERTEX.y = mix(VERTEX.y, VERTEX.y * (0.9 + noise_value * 0.2), terrain_smoothing);
    }

    // Animate grass
    if (VERTEX.y < grass_max_height) {
        // Calculate grass influence based on height
        float grass_influence = 1.0 - smoothstep(grass_min_height, grass_max_height, VERTEX.y);

        // Wind effect (time-based animation)
        vec3 wind = normalize(wind_direction);
        float wind_time = TIME * wind_speed;

        // Different frequencies of noise-based movement
        float noise1 = sin(wind_time + world_position.x * 0.1) * 0.5 + 0.5;
        float noise2 = cos(wind_time * 0.7 + world_position.y * 0.1) * 0.5 + 0.5;

        // Combine noises and apply movement to upper vertices
        float height_factor = smoothstep(vertex_y - grass_blade_height, vertex_y, VERTEX.y);
        vec3 wind_offset = wind * noise1 * noise2 * wind_strength * height_factor * grass_influence;

        // Only apply wind to vertices that should be affected by grass
        VERTEX += wind_offset * grass_influence;
    }
}

void fragment() {
    // Apply texture scaling
    vec2 scaled_uv = UV * uv_scale;

    // Sample base textures
    vec3 grass_tex_color = texture(terrain_grass, scaled_uv).rgb;
    vec3 rock_tex_color = texture(terrain_rock, scaled_uv).rgb;

    // Sample normal maps (convert from [0,1] to [-1,1] range)
    vec3 grass_normal = texture(terrain_grass_normal, scaled_uv).rgb * 2.0 - 1.0;
    vec3 rock_normal = texture(terrain_rock_normal, scaled_uv).rgb * 2.0 - 1.0;

    // Add some variation to UVs based on world position for less obvious tiling
    vec2 offset_uv = scaled_uv + vec2(
        perlin_noise(world_position * 0.05) * 0.1,
        perlin_noise(world_position * 0.05 + vec2(100.0)) * 0.1
    );

    // Add detail noise to textures
    float detail_noise = fbm(world_position * 0.2, 3);

    // Height-based weight calculation with smoothing
    float grass_weight = 1.0 - smoothstep(grass_min_height, grass_max_height, vertex_y);
    float rock_weight = smoothstep(grass_min_height, grass_max_height, vertex_y);

    // Apply slope-based blending (less grass on steep slopes)
    float slope = 1.0 - dot(normalize(vertex_normal), vec3(0.0, 1.0, 0.0));
    grass_weight *= 1.0 - smoothstep(0.1, 0.4, slope);
    rock_weight = mix(rock_weight, rock_weight + grass_weight * slope, slope);

    // Apply some noise variation to the weights for more natural transitions
    float noise_variation = texture(noise_texture, world_position * 0.05).r * 0.4 - 0.2;
    grass_weight = clamp(grass_weight + noise_variation * grass_weight, 0.0, 1.0);
    rock_weight = clamp(rock_weight - noise_variation * rock_weight, 0.0, 1.0);

    // Normalize weights to ensure they sum to 1.0
    float total_weight = grass_weight + rock_weight;
    grass_weight /= total_weight;
    rock_weight /= total_weight;

    // Blend colors
    vec3 final_color = grass_tex_color * grass_weight + rock_tex_color * rock_weight;

    // Blend normal maps using the same weights
    vec3 blended_normal = normalize(grass_normal * grass_weight + rock_normal * rock_weight);

    // Apply normal strength
    blended_normal = normalize(mix(vec3(0.0, 0.0, 1.0), blended_normal, normal_strength));

    // Add small grass effect to grass areas
    if (grass_weight > 0.1) {
        // Generate procedural grass pattern
        float grass_pattern = 0.0;

        // Create small scale noise for grass blades
        float micro_noise = fbm(offset_uv * 20.0, 2);

        // Create varied grass blades
        for (int i = 0; i < 3; i++) {
            float blade_pos = fract(offset_uv.x * 50.0 + float(i) * 0.33 + micro_noise * 2.0);
            float blade_shape = smoothstep(grass_blade_width, 0.0, abs(blade_pos - 0.5)) * grass_density;
            grass_pattern += blade_shape * (0.5 + 0.5 * sin(offset_uv.y * 100.0 + blade_pos * 6.28));
        }

        // Apply grass pattern with height and density controls
        float grass_visibility = grass_pattern * grass_weight * grass_density;

        // Add subtle color variation to grass
        vec3 varied_grass_color = grass_tex_color * (1.0 + (micro_noise - 0.5) * grass_color_variation);

        // Mix in the grass effect
        final_color = mix(final_color, varied_grass_color * 1.2, grass_visibility * 0.2);
    }

    // Apply enhanced detail based on height and slope
    float detail_enhancement = mix(0.8, 1.2, detail_noise);

    // Set final material properties
    ALBEDO = final_color * detail_enhancement;
    ROUGHNESS = mix(0.7, 0.9, rock_weight); // Rock is rougher than grass
    METALLIC = 0.0; // Natural terrain isn't metallic
    NORMAL_MAP = blended_normal;

    // Optional rim lighting effect for grass
    if (grass_weight > 0.5) {
        // Add subtle SSS effect for grass
        SSS_STRENGTH = 0.3 * grass_weight;
    }
}