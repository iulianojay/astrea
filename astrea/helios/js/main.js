

// ---------- Metrics ----------
function updateMetrics() {
    const throughputStr = stats.throughput.toLocaleString(undefined, { maximumFractionDigits: 0 });
    document.getElementById("metrics").innerHTML = [
        `<div class="container">`,
        `<li><strong>${stats.objects.toLocaleString()}</strong> propagated objects</li>`,
        `<li><strong>${stats.propMinutes.toFixed(1)} min</strong> prop &nbsp;·&nbsp; <strong>${stats.stepMinutes.toFixed(1)} min</strong> step &nbsp;·&nbsp; <strong>${stats.nFrames}</strong> frames</li>`,
        `<li><strong>${stats.elapsedMs.toFixed(1)} ms</strong> propagation &nbsp;·&nbsp; <strong>${throughputStr}</strong> obj/s</li>`,
        `<li id="simtime"><strong>T+0.0 min</strong></li>`,
        `</div>`
    ].join("");
}

// ---------- Altitude colour ----------
function calculateColorByAltitude(x, y, z) {
    const r = Math.sqrt(x * x + y * y + z * z);
    const alt = r - numeric.earthRadiusKm;
    const maxAlt = numeric.maxRadiusKm - numeric.earthRadiusKm;
    const t = Math.max(0, Math.min(1, alt / Math.max(1, maxAlt)));
    const hue = 240 * t; // blue (LEO) → red (HEO)
    return `hsl(${hue.toFixed(0)},100%,65%)`;
}

// Updates the scene with a new propagation result
function updatePropagation(result) {
    frames = result.frames;
    numeric = result.numeric;
    stats = result.stats;
    state.simProgress = 0;
    state.speed = 1.0;
    document.getElementById("speedSlider").value = state.speed;
    document.getElementById("speedVal").textContent = state.speed.toFixed(1) + "×";
    updateMetrics();
}

// ---------- Resize ----------
function resize() {
    const dpr = Math.max(1, Math.min(2, window.devicePixelRatio || 1));
    canvas.width = Math.floor(window.innerWidth * dpr);
    canvas.height = Math.floor(window.innerHeight * dpr);
    context.setTransform(dpr, 0, 0, dpr, 0, 0);
}

// ---------- Draw ----------
function draw() {
    if (frames.length > 1) {
        state.simProgress = (state.simProgress + state.speed / stats.nFrames) % frames.length;
    }
    const f0 = Math.floor(state.simProgress) % frames.length;
    const f1 = (f0 + 1) % frames.length;
    const blend = state.simProgress - Math.floor(state.simProgress);

    const simEl = document.getElementById("simtime");
    if (simEl) { simEl.innerHTML = `<strong>T+${(f0 * stats.stepMinutes).toFixed(1)} min</strong>`; }

    const w = window.innerWidth, h = window.innerHeight;
    const cx = w * 0.5, cy = h * 0.54;

    context.clearRect(0, 0, w, h);

    const span = Math.max(numeric.maxRadiusKm, numeric.earthRadiusKm * 1.6);
    const scale = Math.min(w, h) * 0.43 / span * state.zoom;

    const cosA = Math.cos(state.az), sinA = Math.sin(state.az);
    const cosE = Math.cos(state.el), sinE = Math.sin(state.el);

    // Project ECI [x,y,z] → canvas {x, y, z (depth), d (perspective factor)}
    const project = (p) => {
        const rx = p[0] * cosA + p[1] * sinA;
        const ry = -p[0] * sinA + p[1] * cosA;
        const rz = p[2];
        const fx = rx * cosE + rz * sinE;
        const fy = ry;
        const fz = -rx * sinE + rz * cosE;
        const depth = 1.0 / (1.0 + fx / (span * 2.8));
        return { x: cx + fy * scale * depth, y: cy - fz * scale * depth, z: fx, d: depth };
    };

    const earthCenter = project([0, 0, 0]);

    // Earth radius in pixels: scale-based only, not perspective-distorted
    const earthRadiusPx = Math.max(2, numeric.earthRadiusKm * scale);

    // // Atmospheric glow
    // const glow = context.createRadialGradient(
    //     earthCenter.x, earthCenter.y, earthRadiusPx * 0.4,
    //     earthCenter.x, earthCenter.y, earthRadiusPx * 2.5
    // );
    // glow.addColorStop(0, "rgba(94,178,255,0.30)");
    // glow.addColorStop(1, "rgba(94,178,255,0.00)");
    // context.fillStyle = glow;
    // context.beginPath();
    // context.arc(earthCenter.x, earthCenter.y, earthRadiusPx * 1.1, 0, Math.PI * 2);
    // context.fill();

    // Earth body
    context.fillStyle = state.earthColor;
    context.beginPath();
    context.arc(earthCenter.x, earthCenter.y, earthRadiusPx, 0, Math.PI * 2);
    context.fill();

    // // Latitude lines
    // context.strokeStyle = "rgba(208,235,255,0.24)";
    // context.lineWidth = 1;
    // for (let i = -9; i <= 9; i++) {
    //     const yOff = i * earthRadiusPx * 0.1;
    //     const rx2 = earthRadiusPx * Math.sqrt(Math.max(0, 1 - Math.pow(yOff / earthRadiusPx, 2)));
    //     context.beginPath();
    //     context.ellipse(earthCenter.x, earthCenter.y + yOff, rx2, rx2 * 0.22, 0, 0, Math.PI * 2);
    //     context.stroke();
    // }

    // Objects – coloured by current altitude
    const frame0 = frames[f0], frame1 = frames[f1];
    for (let iFrame = 0; iFrame < frame0.length; iFrame++) {
        // Interpolate between the two frames
        const a = frame0[iFrame], b = frame1[iFrame];
        const lx = a[0] + blend * (b[0] - a[0]);
        const ly = a[1] + blend * (b[1] - a[1]);
        const lz = a[2] + blend * (b[2] - a[2]);

        // Project to screen space
        const p = project([lx, ly, lz]);
        if (p.z > span * 0.9) { continue; }

        // Size and alpha based on perspective depth
        const alpha = Math.max(0.18, Math.min(1, 0.22 + 0.78 * p.d));
        const r = Math.max(0.7, Math.min(2.3, 1.1 * p.d));

        // Colour based on altitude
        context.fillStyle = calculateColorByAltitude(lx, ly, lz);
        context.globalAlpha = alpha;
        context.beginPath();
        context.arc(p.x, p.y, r, 0, Math.PI * 2);
        context.fill();
    }
    context.globalAlpha = 1.0;

    requestAnimationFrame(draw);
}

// Function to create multiple stars
function createStars() {
    const numberOfStars = 500;
    for (let i = 0; i < numberOfStars; i++) {
        const star = document.createElement('div');
        star.classList.add('star');

        // Random size, and position for each star
        const size = Math.random() * 1 + 1;
        star.style.width = `${size}px`;
        star.style.height = `${size}px`;
        star.style.left = `${Math.random() * 100}vw`;
        star.style.top = `${Math.random() * 100}vh`;

        document.body.appendChild(star);
    }
}