<p align="center">
  <a href="#how-to-build">How to Build</a> •
  <a href="#running">How to Run</a> •

</p>

<h2><a id="user-content-whats-tron" class="anchor" aria-hidden="true" href="#whats-tron"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M4 9h1v1H4c-1.5 0-3-1.69-3-3.5S2.55 3 4 3h4c1.45 0 3 1.69 3 3.5 0 1.41-.91 2.72-2 3.25V8.59c.58-.45 1-1.27 1-2.09C10 5.22 8.98 4 8 4H4c-.98 0-2 1.22-2 2.5S3 9 4 9zm9-3h-1v1h1c1 0 2 1.22 2 2.5S13.98 12 13 12H9c-.98 0-2-1.22-2-2.5 0-.83.42-1.64 1-2.09V6.25c-1.09.53-2 1.84-2 3.25C6 11.31 7.55 13 9 13h4c1.45 0 3-1.69 3-3.5S14.5 6 13 6z"></path></svg></a>What's Thread Pool</h2>
<p>Coin Server aims to manage blockchain related operations for casino and exposes api for interacting with network</p>
<p>Application provides api which is sufficient to conduct main processes into public blockchain network. Simple interface enables users to Generate new wallets (maybe with registering new accounts in blockchain), Make withdrawal transaction, and Receive transaction states (canceled, unconfirmed confirmed) about wallets which are of our interest (withdraw, or generated deposit wallets) </p>
<p>Internally application is divided into four main parts <strong>1. Blockchain Parser</strong>, <strong>2. Balance Service</strong>, <strong>3. Wallet Generator</strong>. <strong>4. Thrift Server Communication</strong> which direct all incoming requests and processes</p>

<h1><a id="user-content-how-to-build" class="anchor" aria-hidden="true" href="#how-to-build"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M4 9h1v1H4c-1.5 0-3-1.69-3-3.5S2.55 3 4 3h4c1.45 0 3 1.69 3 3.5 0 1.41-.91 2.72-2 3.25V8.59c.58-.45 1-1.27 1-2.09C10 5.22 8.98 4 8 4H4c-.98 0-2 1.22-2 2.5S3 9 4 9zm9-3h-1v1h1c1 0 2 1.22 2 2.5S13.98 12 13 12H9c-.98 0-2-1.22-2-2.5 0-.83.42-1.64 1-2.09V6.25c-1.09.53-2 1.84-2 3.25C6 11.31 7.55 13 9 13h4c1.45 0 3-1.69 3-3.5S14.5 6 13 6z"></path></svg></a>How to Build</h1>
<h2><a id="user-content-prepare-dependencies" class="anchor" aria-hidden="true" href="#prepare-dependencies"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M4 9h1v1H4c-1.5 0-3-1.69-3-3.5S2.55 3 4 3h4c1.45 0 3 1.69 3 3.5 0 1.41-.91 2.72-2 3.25V8.59c.58-.45 1-1.27 1-2.09C10 5.22 8.98 4 8 4H4c-.98 0-2 1.22-2 2.5S3 9 4 9zm9-3h-1v1h1c1 0 2 1.22 2 2.5S13.98 12 13 12H9c-.98 0-2-1.22-2-2.5 0-.83.42-1.64 1-2.09V6.25c-1.09.53-2 1.84-2 3.25C6 11.31 7.55 13 9 13h4c1.45 0 3-1.69 3-3.5S14.5 6 13 6z"></path></svg></a>Prepare dependencies</h2>
<h3>enter thread pool directory and just execute 'make'</h3>
<h2><a id="user-content-getting-the-code-with-git" class="anchor" aria-hidden="true" href="#getting-the-code-with-git"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M4 9h1v1H4c-1.5 0-3-1.69-3-3.5S2.55 3 4 3h4c1.45 0 3 1.69 3 3.5 0 1.41-.91 2.72-2 3.25V8.59c.58-.45 1-1.27 1-2.09C10 5.22 8.98 4 8 4H4c-.98 0-2 1.22-2 2.5S3 9 4 9zm9-3h-1v1h1c1 0 2 1.22 2 2.5S13.98 12 13 12H9c-.98 0-2-1.22-2-2.5 0-.83.42-1.64 1-2.09V6.25c-1.09.53-2 1.84-2 3.25C6 11.31 7.55 13 9 13h4c1.45 0 3-1.69 3-3.5S14.5 6 13 6z"></path></svg></a>Getting the code with git and build</h2>
<ul>
<li>Use Git from the Terminal, see the <a href="https://help.github.com/articles/set-up-git/">Setting up Git</a> and <a href="https://help.github.com/articles/fork-a-repo/">Fork a Repo</a> articles.</li>
<li>develop branch: the newest code</li>
<li>master branch: more stable than develop.
In the shell command, type:</li>
</ul>
<div class="highlight highlight-source-shell"><pre>
git clone https://gitlab.cloudhosted.io/fortunejack/coin-server-v2.git
cd coin-server-v2
//during update might be needed "make clean" first
make DEFAULTCONF=Release
</pre></div>


<h1><a id="user-content-running" class="anchor" aria-hidden="true" href="#running"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M4 9h1v1H4c-1.5 0-3-1.69-3-3.5S2.55 3 4 3h4c1.45 0 3 1.69 3 3.5 0 1.41-.91 2.72-2 3.25V8.59c.58-.45 1-1.27 1-2.09C10 5.22 8.98 4 8 4H4c-.98 0-2 1.22-2 2.5S3 9 4 9zm9-3h-1v1h1c1 0 2 1.22 2 2.5S13.98 12 13 12H9c-.98 0-2-1.22-2-2.5 0-.83.42-1.64 1-2.09V6.25c-1.09.53-2 1.84-2 3.25C6 11.31 7.55 13 9 13h4c1.45 0 3-1.69 3-3.5S14.5 6 13 6z"></path></svg></a>Running</h1>


<details>
<summary>Correct output</summary>
<div class="highlight highlight-source-shell"><pre>
Thread Started
task - 5  in progress
Thread Started
task - 5  in progress
Thread Started
task - 5  in progress
task - 5 finished
task - 5 finished
task - 5  in progress
task - 5  in progress
task - 5 finished
task - 5  in progress
^C^Ctask - 5 finished
task - 5 finished
task - 5 finished
Test 1: Success
Thread Started
task - 5  in progress
....
</pre></div>
