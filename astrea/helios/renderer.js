// Three.js scene initialization (renderer process)
try {
    const THREE             = require('three');
    const { OrbitControls } = require('three/examples/jsm/controls/OrbitControls.js');

    console.log('Three.js loaded, version:', THREE.REVISION);

    // Scene setup
    const scene  = new THREE.Scene();
    const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 10000);
    camera.position.set(0, 0, 3);

    const renderer = new THREE.WebGLRenderer({ antialias: true, alpha: false, powerPreference: "high-performance" });
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.toneMapping         = THREE.ACESFilmicToneMapping;
    renderer.toneMappingExposure = 1.0;

    const container = document.getElementById('canvas-container');
    container.appendChild(renderer.domElement);
    console.log('Renderer created and added to DOM');

    // Orbit Controls
    const controls         = new OrbitControls(camera, renderer.domElement);
    controls.enableDamping = true;
    controls.dampingFactor = 0.05;
    controls.minDistance   = 1.5;
    controls.maxDistance   = 100;
    controls.enablePan     = true;

    // Texture loader
    const textureLoader = new THREE.TextureLoader();

    // Create starfield
    function createStarfield()
    {
        const starsGeometry = new THREE.BufferGeometry();
        const starsMaterial = new THREE.PointsMaterial(
            { color: 0xffffff, size: 0.7, sizeAttenuation: true, transparent: true, opacity: 0.8 }
        );

        const starsVertices = [];
        for (let i = 0; i < 10000; i++) {
            const radius = 500 + Math.random() * 500;
            const theta  = Math.random() * Math.PI * 2;
            const phi    = Math.acos(2 * Math.random() - 1);

            const x = radius * Math.sin(phi) * Math.cos(theta);
            const y = radius * Math.sin(phi) * Math.sin(theta);
            const z = radius * Math.cos(phi);

            starsVertices.push(x, y, z);
        }

        starsGeometry.setAttribute('position', new THREE.Float32BufferAttribute(starsVertices, 3));
        const stars = new THREE.Points(starsGeometry, starsMaterial);
        scene.add(stars);

        return stars;
    }

    // Create Earth with textures
    function createEarth()
    {
        const earthGeometry = new THREE.SphereGeometry(1, 64, 64);

        // Load textures
        const earthTexture      = textureLoader.load('images/earthmap.jpg');
        earthTexture.colorSpace = THREE.SRGBColorSpace;

        const cloudsTexture      = textureLoader.load('images/cloud_combined.jpg');
        cloudsTexture.colorSpace = THREE.SRGBColorSpace;

        const lightsTexture      = textureLoader.load('images/earth_lights.png');
        lightsTexture.colorSpace = THREE.SRGBColorSpace;

        // Earth material
        const earthMaterial = new THREE.MeshPhongMaterial({
            map: earthTexture,
            bumpScale: 0.03,
            specular: new THREE.Color(0x333333),
            shininess: 10,
            emissiveMap: lightsTexture,
            emissive: new THREE.Color(0xffff88),
            emissiveIntensity: 0.5
        });

        const earth = new THREE.Mesh(earthGeometry, earthMaterial);
        scene.add(earth);

        // Clouds layer
        const cloudsGeometry = new THREE.SphereGeometry(1.01, 64, 64);
        const cloudsMaterial =
            new THREE.MeshPhongMaterial({ map: cloudsTexture, transparent: true, opacity: 0.4, depthWrite: false });

        const clouds = new THREE.Mesh(cloudsGeometry, cloudsMaterial);
        earth.add(clouds);

        return { earth, clouds };
    }

    // Create atmosphere glow
    function createAtmosphere()
    {
        const atmosphereGeometry = new THREE.SphereGeometry(1.15, 64, 64);
        const atmosphereMaterial = new THREE.ShaderMaterial({
            transparent: true,
            side: THREE.BackSide,
            blending: THREE.AdditiveBlending,
            vertexShader: `
                    varying vec3 vNormal;
                    void main() {
                        vNormal = normalize(normalMatrix * normal);
                        gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
                    }
                `,
            fragmentShader: `
                    varying vec3 vNormal;
                    void main() {
                        float intensity = pow(0.6 - dot(vNormal, vec3(0.0, 0.0, 1.0)), 2.0);
                        gl_FragColor = vec4(0.3, 0.6, 1.0, 1.0) * intensity;
                    }
                `
        });

        const atmosphere = new THREE.Mesh(atmosphereGeometry, atmosphereMaterial);
        scene.add(atmosphere);

        return atmosphere;
    }

    // Lighting (Sun as distant light source)
    function setupLighting()
    {
        // Ambient light for overall illumination
        const ambientLight = new THREE.AmbientLight(0x222222, 0.5);
        scene.add(ambientLight);

        // Sun as directional light (distant light source)
        const sunLight = new THREE.DirectionalLight(0xffffff, 2.0);
        sunLight.position.set(5, 2, 3);
        scene.add(sunLight);

        // Add subtle hemisphere light for atmospheric effect
        const hemiLight = new THREE.HemisphereLight(0x4488ff, 0x002244, 0.3);
        scene.add(hemiLight);

        return { ambientLight, sunLight, hemiLight };
    }

    // Initialize scene
    console.log('Creating starfield...');
    const starfield = createStarfield();
    console.log('Creating Earth...');
    const { earth, clouds } = createEarth();
    console.log('Creating atmosphere...');
    const atmosphere = createAtmosphere();
    console.log('Setting up lighting...');
    const lights = setupLighting();
    console.log('Scene initialized successfully');

    // Animation loop
    function animate()
    {
        requestAnimationFrame(animate);

        // Rotate Earth slowly
        earth.rotation.y += 0.0005;

        // Rotate clouds slightly faster
        clouds.rotation.y += 0.0007;

        // Subtle starfield rotation
        starfield.rotation.y += 0.00002;

        // Update controls
        controls.update();

        // Render
        renderer.render(scene, camera);
    }

    // Handle window resize
    window.addEventListener('resize', () => {
        camera.aspect = window.innerWidth / window.innerHeight;
        camera.updateProjectionMatrix();
        renderer.setSize(window.innerWidth, window.innerHeight);
    });

    // Start animation
    console.log('Starting animation loop');
    animate();
}
catch (error) {
    console.error('Error initializing Three.js:', error);
    const info         = document.getElementById('info');
    const errorP       = document.createElement('p');
    errorP.style.color = '#f00';
    errorP.textContent = 'Error: ' + error.message;
    info.appendChild(errorP);
}
