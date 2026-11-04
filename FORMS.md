# Answer submission: organizer guide

Students submit their pre-exercise answers through **one permanent Google Form**, shared by all
episodes and all years. Each episode page shows a "Submit your answers" box
(`_includes/submit.md`) linking to the form with the **school year** and **episode** pre-filled.
Responses land in a Google Sheet, where `tools/forms/grade.gs` builds a per-student dashboard.

The form and sheet should be owned by a shared CMSDAS organizer Google account (not a personal
one) so they survive organizer turnover.

## Yearly checklist

1. Bump `year:` in `_config.yml`. This updates every page and every pre-filled form link.
2. In the sheet's **Key** tab, add a row with the new year for any question whose expected
   answer changed (for example a new input file or CMSSW release).
3. After the first few submissions, check the **Dashboard** tab.

You do **not** need to create a new form or edit any form links.

## One-time setup

### 1. Create the form

Create a form with these questions on the first page. The grading script finds columns by the
words shown in bold, so keep those in the titles:

| Title | Type | Notes |
|---|---|---|
| (email) | Settings → Responses → Collect email addresses | Becomes the `Email Address` column |
| Please enter your **name** (FirstName LastName) | Short answer, required | |
| Please enter your **Fermilab username** | Short answer, required | |
| Please enter your CERN username | Short answer | Optional; not used by the script |
| **School year** | Short answer, required | Pre-filled from `site.year` |
| Which **episode**? | Dropdown, required | Options exactly `Episode 1` … `Episode 6`; "Go to section based on answer" |

Then add one section per episode. Each question title starts with its ID (`Question 3.1: …`),
matching the `## Question N.M` boxes in `_episodes/`:

| Section | Questions |
|---|---|
| Episode 1 | `Question 1.1` |
| Episode 2 | 2.1, 2.2, 2.3 |
| Episode 3 | 3.1, 3.2 |
| Episode 4 | 4.1 (paragraph) |
| Episode 5 | 5.1, 5.2, 5.3, 5.4 |
| Episode 6 | 6.1, 6.4, 6.5 (paragraph); 6.2, 6.3 |

Make each episode section end with "Submit form", so a student only sees one episode's questions.
Allow multiple responses per person; the dashboard keeps the latest submission for each episode.

### 2. Wire it into the site

1. In the form, open ⋮ → **Get pre-filled link**, type `2099` as the school year, pick `Episode 1`, and
   click **Get link**. The link looks like
   `https://docs.google.com/forms/d/e/<ID>/viewform?usp=pp_url&entry.111=2099&entry.222=Episode+1`.
2. Copy the pieces into `_config.yml`:
   ```yaml
   submission:
     form_url: "https://docs.google.com/forms/d/e/<ID>/viewform"
     year_entry: "entry.111"
     episode_entry: "entry.222"
   ```
   Until `form_url` is set, the episode pages say the form is not open yet.

### 3. Set up grading

1. From the form's **Responses** tab, link it to a new spreadsheet.
2. Add a tab named **Key** with this header row, then one row per question:

   | Question | Year | Check | Expected | Tolerance |
   |---|---|---|---|---|
   | 3.1 | | number | *(value)* | 0 |
   | 3.2 | | number | *(value)* | 0.05 |
   | 2.3 | | regex | `^\s*NNM\s*$` | |
   | 2.1 | | regex | `success:\s*\S+\s+\S+` | |

   - **Check** is `number` (first number in the answer within *Tolerance* of *Expected*),
     `regex` (case-insensitive match), or `any` (just non-empty).
   - Leave **Year** blank for an answer that holds every year; add a row with a year to override it.
   - Questions with no Key row only need a non-empty answer. Per-student answers (2.1, 2.2, 5.1,
     5.3, 6.1, 6.4) should get a format `regex` at most.
   - **Never commit expected answers to this repository**; it is public.
3. Open **Extensions → Apps Script**, paste in `tools/forms/grade.gs`, and run `installTrigger` once
   (authorize when asked). Each submission now rebuilds the **Dashboard** tab: one row per student
   and year, ✅/❌ with the number of correct answers per episode, and a list of questions that need
   attention. Run `updateDashboard` by hand after editing the Key tab.

## Adding or changing a question

1. Edit the `> ## Question N.M` box in the episode under `_episodes/`.
2. Add or edit the matching `Question N.M: …` question in that episode's form section.
3. Add or update its row in the **Key** tab.
