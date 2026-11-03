/**
 * Grading and completion tracking for the permanent CMSDAS pre-exercise answer form.
 *
 * Paste this file into the response spreadsheet (Extensions -> Apps Script) and run
 * `installTrigger` once. Every new submission then rebuilds the "Dashboard" tab.
 * Setup and the expected layout of the "Key" tab are described in FORMS.md.
 *
 * The answer key lives only in the private spreadsheet, never in this public repository.
 */

var RESPONSES_SHEET = 'Form Responses 1';
var KEY_SHEET = 'Key';
var DASHBOARD_SHEET = 'Dashboard';
var EPISODES = [1, 2, 3, 4, 5, 6];

function installTrigger() {
  ScriptApp.newTrigger('updateDashboard')
    .forSpreadsheet(SpreadsheetApp.getActive())
    .onFormSubmit()
    .create();
}

function updateDashboard() {
  var ss = SpreadsheetApp.getActive();
  var responses = ss.getSheetByName(RESPONSES_SHEET).getDataRange().getValues();
  var key = ss.getSheetByName(KEY_SHEET).getDataRange().getValues();
  var rows = buildDashboard(responses, key);

  var out = ss.getSheetByName(DASHBOARD_SHEET) || ss.insertSheet(DASHBOARD_SHEET);
  out.clearContents();
  out.getRange(1, 1, rows.length, rows[0].length).setValues(rows);
  out.setFrozenRows(1);
}

/**
 * Pure function (no Apps Script services) so it can be tested with node.
 * responses: 2D array from the form's response tab, header row first.
 * key:       2D array from the Key tab: Question | Year | Check | Expected | Tolerance.
 * Returns a 2D array: one row per (student, year), one column per episode, then a details column.
 */
function buildDashboard(responses, key) {
  var header = responses[0].map(String);
  var col = function (pattern) {
    for (var i = 0; i < header.length; i++) if (pattern.test(header[i])) return i;
    return -1;
  };
  var cTime = col(/^timestamp/i);
  var cEmail = col(/^e-?mail/i);
  var cName = col(/^name/i);
  var cUser = col(/^cmslpc username/i);
  var cYear = col(/^school year/i);
  var cEpisode = col(/^episode/i);

  // Question columns: headers that start with an ID such as "Q3.1" or "3.1".
  var questionCols = {};
  header.forEach(function (h, i) {
    var m = h.match(/^Q?\s*(\d+\.\d+)/i);
    if (m) questionCols[m[1]] = i;
  });

  // Keep only the latest submission per (email, year, episode).
  var latest = {};
  responses.slice(1).forEach(function (r) {
    var email = String(r[cEmail]).trim().toLowerCase();
    var episode = String(r[cEpisode]).replace(/\D/g, '');
    if (!email || !episode) return;
    var id = [email, r[cYear], episode].join('|');
    if (!latest[id] || new Date(r[cTime]) >= new Date(latest[id][cTime])) latest[id] = r;
  });

  var students = {};
  Object.keys(latest).forEach(function (id) {
    var r = latest[id];
    var year = String(r[cYear]).trim();
    var episode = Number(String(r[cEpisode]).replace(/\D/g, ''));
    var sid = String(r[cEmail]).trim().toLowerCase() + '|' + year;
    var s = students[sid] || (students[sid] = {
      email: String(r[cEmail]).trim(), name: r[cName], user: r[cUser], year: year, eps: {}, wrong: []
    });

    var nRight = 0, nTotal = 0;
    Object.keys(questionCols).forEach(function (q) {
      if (Number(q.split('.')[0]) !== episode) return;
      nTotal++;
      if (checkAnswer(r[questionCols[q]], findKey(key, q, year))) nRight++;
      else s.wrong.push(q);
    });
    s.eps[episode] = nRight === nTotal ? '✅ ' + nRight + '/' + nTotal : '❌ ' + nRight + '/' + nTotal;
  });

  var rows = [['Email', 'Name', 'cmslpc username', 'Year']
    .concat(EPISODES.map(function (e) { return 'Ep ' + e; }))
    .concat(['Needs attention'])];
  Object.keys(students).sort().forEach(function (sid) {
    var s = students[sid];
    rows.push([s.email, s.name, s.user, s.year]
      .concat(EPISODES.map(function (e) { return s.eps[e] || ''; }))
      .concat([s.wrong.sort().join(', ')]));
  });
  return rows;
}

/** The Key row for a question: a row for this exact year wins over a row with a blank year. */
function findKey(key, question, year) {
  var fallback = null;
  for (var i = 1; i < key.length; i++) {
    if (String(key[i][0]).replace(/^Q/i, '').trim() !== question) continue;
    var y = String(key[i][1]).trim();
    if (y === String(year)) return key[i];
    if (y === '') fallback = key[i];
  }
  return fallback;
}

/**
 * Key row columns: Question | Year | Check | Expected | Tolerance.
 *   number: the first number in the answer is within Tolerance of Expected (commas ignored)
 *   regex:  the answer matches Expected (case-insensitive)
 *   any:    the answer is non-empty (no key row behaves the same way)
 */
function checkAnswer(answer, keyRow) {
  var text = String(answer == null ? '' : answer).trim();
  if (!text) return false;
  if (!keyRow) return true;
  var check = String(keyRow[2]).trim().toLowerCase();
  if (check === 'number') {
    var m = text.replace(/,/g, '').match(/-?\d+(\.\d+)?([eE][-+]?\d+)?/);
    if (!m) return false;
    return Math.abs(Number(m[0]) - Number(keyRow[3])) <= Number(keyRow[4] || 0);
  }
  if (check === 'regex') return new RegExp(String(keyRow[3]), 'i').test(text);
  return true;
}

if (typeof module !== 'undefined') module.exports = { buildDashboard: buildDashboard, checkAnswer: checkAnswer };
