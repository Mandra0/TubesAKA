async function startBenchmark() {
    const nMax = parseInt(document.getElementById('nVal').value);
    const k = parseInt(document.getElementById('kVal').value);
    const table = document.getElementById('resTable');
    const consoleLog = document.getElementById('logConsole');

    table.innerHTML = ""; 
    consoleLog.innerHTML = `<p style="color: #38bdf8">> Memulai Analisis Benchmark (N: ${nMax}, K: ${k})...</p>`;

    const steps = [0.2, 0.4, 0.6, 0.8, 1.0].map(p => Math.round(nMax * p));

    for (let n of steps) {
        const logEntry = document.createElement('p');
        logEntry.innerText = `> Menjalankan komputasi untuk N = ${n}...`;
        consoleLog.appendChild(logEntry);
        consoleLog.scrollTop = consoleLog.scrollHeight; 

        try {
            const res = await fetch('/api/analyze_single', {
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify({n, k})
            });
            const data = await res.json();

            table.innerHTML += `<tr>
                <td>${n}</td>
                <td>${data.iter.toFixed(3)}</td>
                <td>${data.rec.toFixed(3)}</td>
                <td style="color:#38bdf8; font-weight:bold">${data.hyb.toFixed(3)}</td>
            </tr>`;

            logEntry.innerHTML = `> <span style="color:#22c55e">Selesai:</span> N=${n} diproses. (Hybrid: ${data.hyb.toFixed(2)}ms)`;
            consoleLog.scrollTop = consoleLog.scrollHeight;

        } catch (e) {
            logEntry.innerHTML = `> <span style="color:red">Error:</span> Gagal memproses N=${n}.`;
        }
    }
    
    consoleLog.innerHTML += `<p style="color: #38bdf8; font-weight:bold">> SEMUA TAHAPAN BERHASIL DISELESAIKAN!</p>`;
    consoleLog.scrollTop = consoleLog.scrollHeight;
}