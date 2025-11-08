// server.js
// Minimal Express server that serves the web UI and runs the assembler executable.
// POST /assemble  { code: "assembly text" } -> returns assembler output (plain text)

const express = require('express');
const path = require('path');
const { spawn } = require('child_process');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json({ limit: '1mb' })); // parse JSON bodies
app.use(express.urlencoded({ extended: false }));

// Serve UI from public/
app.use(express.static(path.join(__dirname, 'public')));

// Endpoint to assemble code
app.post('/assemble', async (req, res) => {
  const code = req.body.code;
  if (typeof code !== 'string') {
    return res.status(400).send('Missing "code" in JSON body.');
  }

  // Spawn the assembler executable (must be compiled already)
  // The executable should read stdin, write its output to stdout (our main.cpp wrapper does that)
 const exe = path.join(__dirname, 'assembler_runtime.exe');
 // adjust if you named it differently

  const child = spawn(exe, [], { stdio: ['pipe', 'pipe', 'pipe'] });

  let out = '';
  let err = '';

  child.stdout.on('data', (data) => {
    out += data.toString();
  });

  child.stderr.on('data', (data) => {
    err += data.toString();
  });

  child.on('error', (e) => {
    res.status(500).send('Failed to start assembler executable: ' + e.message);
  });

  child.on('close', (codeExit) => {
    if (err && !out) {
      // if assembler printed errors to stderr and nothing on stdout, return as plain text
      return res.type('text').status(200).send(err);
    }
    // return combined output: stdout then stderr (if any)
    let combined = out;
    if (err) combined += "\n--- STDERR ---\n" + err;
    res.type('text').status(200).send(combined);
  });

  // Send the code to assembler stdin and close
  child.stdin.write(code);
  child.stdin.end();
});

// Quick health route
app.get('/ping', (req, res) => res.send('pong'));

app.listen(PORT, () => {
  console.log(`Server listening on http://localhost:${PORT}`);
  console.log(`Open http://localhost:${PORT} to use the UI`);
});
