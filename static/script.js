// Helper function for POST requests
async function postJSON(path, body) {
  const res = await fetch(path, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(body)
  });
  return res.json();
}

// Allocation simulator
document.getElementById('runAlloc').addEventListener('click', async () => {
  const memsize = parseInt(document.getElementById('memsize').value);
  const alg = document.getElementById('alg').value;
  let procs = [];

  try {
    procs = JSON.parse(document.getElementById('procs').value);
  } catch (e) {
    alert('Invalid JSON for processes');
    return;
  }

  const body = { memory_size: memsize, processes: procs, algorithm: alg };
  const out = await postJSON('/simulate_allocation', body);

  // Display result
  document.getElementById('output').textContent = JSON.stringify(out, null, 2);

  // Save latest simulation in localStorage for results.html
  localStorage.setItem('last_sim', JSON.stringify(out));
});

// Paging simulator
document.getElementById('runPage').addEventListener('click', async () => {
  const frames = parseInt(document.getElementById('frames').value);
  const refs = document
    .getElementById('refs')
    .value.split(',')
    .map(x => x.trim())
    .filter(x => x !== '')
    .map(Number);

  const policy = document.getElementById('policy').value;
  const out = await postJSON('/simulate_paging', { frames, refs, policy });

  // Display result
  document.getElementById('output').textContent = JSON.stringify(out, null, 2);

  // Save latest simulation in localStorage for results.html
  localStorage.setItem('last_sim', JSON.stringify(out));
});
